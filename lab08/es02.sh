#!/bin/bash

#Realizzare uno script bash che:
#- riceva in ingresso (da riga di comando oppure da tastiera) il nome di un file
#- visualizzi (a video) il numero di caratteri della linea piu' lunga e il numero di righe del file stesso.
#Si supponga che le righe del file non contengano spazi.

# Alternative version (sostituisci poi $1 con $fname
# echo "Please write the name of the file: "; read fname;
 
#CONTROLLO DI AVER PASSATO 1 parametro nomefile
if [ $# -ne 1 ]
then
  echo "Give me ren.... one file's name .-."
  exit 1
fi

nline=$(wc -l $1)
max=0

while read row
do	
	tmp=${#row}
	if [ $tmp -gt $max ] 
	then
		let "max=tmp"
	fi
done <$1

echo "NumberLIne= $nline, MaxNumberChar= $max"

exit 0
