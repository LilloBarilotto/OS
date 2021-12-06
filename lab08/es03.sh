#!/bin/bash

# directory name is in $1

if $# != 1
	echo "Oh come on bro..."
exit 1

for var in $(ls $1)
do
	lowString=$(echo $var | awk '{print tolower($0)}')
	mv $var $lowString
done

exit 0
