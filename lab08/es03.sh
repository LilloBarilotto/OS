#!/bin/bash

# directory name is in $1

if [ $# != 1 ]
then
	echo "Oh come on bro... Give me DIR"
	exit 1
fi

for var in $(ls $1)
do
	lowString=$(echo $var | awk '{print tolower($0)}')
	mv $1/${var} $1/${lowString}
done

exit 0
