#!/bin/bash

namee=""

if [ "$1" = "$namee" ]; then
    echo "Usage: ./trace.sh (ProductID)"

else
    sort -n -t, -k2 *.log | grep -E "$1" > $1.log
    if [[ -s $1.log ]]; then
	cat $1.log
    else
	rm -rf $1.log
	echo "No records found for $1"
    fi 
fi 

