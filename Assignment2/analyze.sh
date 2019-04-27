#!/bin/bash
# My first assignment :)
''> output.txt 2> output1.txt
rm -rf output1.txt
files=`ls 7Eleven_00123*.log | sort -n`
for file in $files
do
	echo $file':' >> output.txt
	cat $file  | sort -n -t- -k3 -s | sed 's#,#-#' | sed 's# #-#' | cut -d '-' -f 1,2,3,5 | sort -n -r | uniq -c | sort -n -r |  head -n3 | sed 's#-# #' | sed 's#-# #' | sed 's#-# #'| awk '{ print $1, $5 }' >> output.txt
done
 
cat output.txt
