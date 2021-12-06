#!/bin/bash

#Realizzare uno script bash che:
#- riceva in ingresso (da riga di comando oppure da tastiera) il nome di un file
#- visualizzi (a video) il numero di caratteri della linea piu' lunga e il numero di righe del file stesso.
#Si supponga che le righe del file non contengano spazi.


echo "Please write the name of the file: "
read fname

nline=$(wc -l $fname)
max=0

while read row
do	
	tmp=${#row}
	if $tmp -gt $max
	then
		let "max=tmp"
	fi
done <$fname

echo "NumberLIne= $nline, MaxNumberChar= $max"

exit 0
