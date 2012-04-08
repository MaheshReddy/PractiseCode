#!/bin/bash

#script to generate random runber file

num=$1

echo "generating "$num" random numbers"

echo $num > rand.txt

for (( i = 1; i <= $num; i++ ))
do
	echo $RANDOM >> rand.txt;
done
