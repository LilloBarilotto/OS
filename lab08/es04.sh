#!/bin/bash

if [ $# != 1 ]; then
	echo "BRO AGAIN 1 F***ING FILE, sorry volevo dire 'Usage...'"
	exit 1
fi

i=0
while read line; do
	for word in $line; do
		
		i=0
		
		while [ $i < ${#words[@]} ]; do
			if [ ${words[$i]} -eq $word ]; then
				let wordsCounter[i]=wordsCounter[i]+1
				break
			fi;
			let i=i+1
		done
		
		if [ $i -eq ${#words[@]} ]; then
			words[$i]=$word;
			wordsCounter[$i]=0
		fi
	done
done <$1

echo "Tie prendite sto conteggio delle parole nel file:"

while [ $i < ${#words[@]} ]; do
	echo " ${words[$i]} -> ${wordsCounter[$i]}"
	let i=i+1
done

exit 0
