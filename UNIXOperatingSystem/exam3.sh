#!/bin/sh
# This program is for monitoring a file.
# Usage: ./exam3.sh filename
# Author: HeRaNO

if [ $# -ne 1 ]
then
	echo "Usage: ./exam3.sh filename"
	exit 0
fi

filename=$1
nowSize=`ls -l|grep $filename$|awk '{print $5}'`
if [ -z $nowSize ]
then
	echo "No such file [ $filename ]."
	exit 0
fi

sizeChange=0
checkCnt=0

clear

while true
do
	nowsta=`ls -l|grep $filename$|awk '{print $5}'`
	if [ $nowSize -ne $nowsta ]
	then
		sizeChange=`expr $sizeChange + 1`
		echo "file [ $filename ] size changed."
		nowSize=$nowsta
		if [ $sizeChange -eq 2 ]
		then
			echo "size change twice. exit."
			exit 0
		fi
	else
		echo "file [ $filename ] size didn't change."
	fi

	checkCnt=`expr $checkCnt + 1`
	if [ $checkCnt -eq 10 ]
	then
		echo "check 10 times. exit."
		exit 0
	fi
	sleep 5s
done

echo "Job done."
exit 0

