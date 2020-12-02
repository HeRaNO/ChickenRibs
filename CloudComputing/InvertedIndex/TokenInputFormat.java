package org.apache.hadoop.examples;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.JobContext;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.TaskAttemptID;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.util.LineReader;

import java.io.IOException;

import java.util.StringTokenizer;


public class TokenInputFormat extends FileInputFormat<Text, ValuePair> {
    /**
     * Don't allow the files to be split!
     */
    @Override
    protected boolean isSplitable(JobContext ctx, Path filename) {
        // ensure the input files are not splittable!  
        return false;
    }

    /**
     * Just return the record reader
     * key is the docno
     */
    public RecordReader<Text, ValuePair> createRecordReader(InputSplit split,
        TaskAttemptContext ctx) throws IOException, InterruptedException {
        return new TokenRecordReader();
    }

    public static class TokenRecordReader extends RecordReader<Text, ValuePair> {
        private long start;
        private long pos;
        private long end;
        private LineReader in;
        private int maxLineLength;
        private Text line;
        private Text key = null;
        private ValuePair value = null;
        private StringTokenizer tokens = null;
        private int tokenPos = 0;
        private String fileID = "0"; // input file id that appears in inverted index  

        public void initialize(InputSplit genericSplit,
            TaskAttemptContext context) throws IOException {
            FileSplit split = (FileSplit) genericSplit;
            Configuration job = context.getConfiguration();
            this.maxLineLength = job.getInt("mapred.linerecordreader.maxlength",
                    Integer.MAX_VALUE);
            start = split.getStart();
            end = start + split.getLength();

            final Path file = split.getPath();
            // Assume file name is an integer of file ID  
            fileID = file.getName();

            FileSystem fs = file.getFileSystem(job);
            FSDataInputStream fileIn = fs.open(split.getPath());
            in = new LineReader(fileIn, job);
            this.pos = start;
            line = new Text();
            key = new Text();
            value = new ValuePair();
        }

        public boolean nextKeyValue() throws IOException {
            boolean splitEnds = false;

            while ((tokens == null) || !tokens.hasMoreTokens()) {
                int lineSize = in.readLine(line, maxLineLength,
                        Math.max((int) Math.min(Integer.MAX_VALUE, end - pos),
                            maxLineLength));

                if (lineSize == 0) {
                    splitEnds = true;

                    break;
                }

                pos += lineSize;
                tokens = new StringTokenizer(line.toString(), " ,");
            }

            if (splitEnds) {
                key = null;
                value = null;
                line = null;
                tokens = null;

                return false;
            } else {
                return true;
            }
        }

        @Override
        public Text getCurrentKey() {
            key.set(tokens.nextToken());
            tokenPos++;

            return key;
        }

        @Override
        public ValuePair getCurrentValue() {
            value.set(fileID, tokenPos);

            return value;
        }

        /**
         * Get the progress within the split
         */
        public float getProgress() {
            if (start == end) {
                return 0.0f;
            } else {
                return Math.min(1.0f, (pos - start) / (float) (end - start));
            }
        }

        public synchronized void close() throws IOException {
            if (in != null) {
                in.close();
            }
        }
    }
}
