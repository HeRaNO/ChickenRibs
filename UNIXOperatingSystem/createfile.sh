#! /bin/sh
# This program is for create a file and add characters automatically at backstage.
# Usage: ./createfile.sh &
# Author: HeRaNO
# WARNING: The PID should be remembered! KILL IT after finishing your job.

filename="afile"

echo "" >> $filename
while true
do
	echo "aaaaaaaaaaaaaaaaa" >> $filename
	sleep 30s
done

