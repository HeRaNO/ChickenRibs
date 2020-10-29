#! /bin/sh
# This program can create a file and save the sentence inputed in the terminal. Terminated when input a null line.
# Usage: ./exam1.sh filename
# Author: HeRaNO

if [ $# -ne 1 ]
then
	echo "Usage: ./exam1.sh filename"
	exit 0
fi

tip="Input a line: (null string to terminate)"
input="foobar"

while true
do
	echo $tip
	read input
	if [ -z "$input" ]
	then
		break
	fi
	echo $input >> $1
done

echo "Job done."

