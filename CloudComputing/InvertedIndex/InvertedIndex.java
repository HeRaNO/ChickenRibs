package org.apache.hadoop.examples;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

import java.io.IOException;

public class InvertedIndex {
    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();

        if (otherArgs.length != 2) {
            System.err.println("Usage: InvertedIndex <in-dir> <out-dir>");
            System.exit(2);
        }

        Job job = new Job(conf, "Inverted Indexer");
        job.setJarByClass(InvertedIndex.class);
        job.setInputFormatClass(TokenInputFormat.class);
        job.setMapperClass(InvertedIndex.TokenizerMapper.class);
        job.setReducerClass(InvertedIndex.IndexReducer.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(ValuePair.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(Text.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }

    public static class TokenizerMapper extends Mapper<Text, ValuePair, Text, ValuePair> {
        @Override
        public void map(Text key, ValuePair value, Context context)
            throws IOException, InterruptedException {
            // TokenInputFormat has generate (word, (fileID, wordPosition))
            // so mapper just split it to reducer
            key.set(key.toString().toLowerCase());
            context.write(key, value);
        }
    }

    public static class IndexReducer extends Reducer<Text, ValuePair, Text, Text> {
        private Text postings = new Text();

        @Override
        public void reduce(Text key, Iterable<ValuePair> values, Context context)
            throws IOException, InterruptedException {
            String list = "";

            for (ValuePair val : values) {
                list += (" " + val.toString());
            }

            postings.set(list);
            context.write(key, postings);
        }
    }
}
