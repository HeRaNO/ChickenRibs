package org.apache.hadoop.examples;

import org.apache.hadoop.io.*;

import java.io.*;


public class ValuePair implements WritableComparable<ValuePair> {
    static {
        WritableComparator.define(ValuePair.class, new Comparator());
    }

    private Text one;
    private IntWritable two;

    public ValuePair() {
        set(new Text(), new IntWritable());
    }

    public ValuePair(Text first, IntWritable second) {
        set(first, second);
    }

    public ValuePair(String first, int second) {
        set(first, second);
    }

    public void set(Text first, IntWritable second) {
        one = first;
        two = second;
    }

    public void set(String first, int second) {
        one.set(first);
        two.set(second);
    }

    public Text getFirst() {
        return one;
    }

    public IntWritable getSecond() {
        return two;
    }

    @Override
    public void write(DataOutput out) throws IOException {
        one.write(out);
        two.write(out);
    }

    @Override
    public void readFields(DataInput in) throws IOException {
        one.readFields(in);
        two.readFields(in);
    }

    @Override
    public int hashCode() {
        return one.hashCode();
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof ValuePair) {
            ValuePair tp = (ValuePair) o;

            return one.equals(tp.one);
        }

        return false;
    }

    @Override
    public String toString() {
        return "(" + one + ", " + two + ")";
    }

    @Override
    public int compareTo(ValuePair tp) {
        int cmp = one.compareTo(tp.one);

        if (cmp != 0) {
            return cmp;
        }

        return two.compareTo(tp.two);
    }

    public static class Comparator extends WritableComparator {
        private static final Text.Comparator TEXT_COMPARATOR = new Text.Comparator();
        private static final IntWritable.Comparator INT_COMPARATOR = new IntWritable.Comparator();

        public Comparator() {
            super(ValuePair.class);
        }

        @Override
        public int compare(byte[] b1, int s1, int l1, byte[] b2, int s2, int l2) {
            try {
                int oneL1 = WritableUtils.decodeVIntSize(b1[s1]) +
                    readVInt(b1, s1);
                int oneL2 = WritableUtils.decodeVIntSize(b2[s2]) +
                    readVInt(b2, s2);
                int cmp = TEXT_COMPARATOR.compare(b1, s1, oneL1, b2, s2, oneL2);

                if (cmp != 0) {
                    return cmp;
                }

                return INT_COMPARATOR.compare(b1, s1 + oneL1, l1 - oneL1, b2,
                    s2 + oneL2, l2 - oneL2);
            } catch (IOException e) {
                throw new IllegalArgumentException(e);
            }
        }

        @Override
        public int compare(WritableComparable a, WritableComparable b) {
            if (a instanceof ValuePair && b instanceof ValuePair) {
                return ((ValuePair) a).compareTo((ValuePair) b);
            }

            return super.compare(a, b);
        }
    }
}
