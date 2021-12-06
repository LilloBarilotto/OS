#!/bin/bash

#Commento del cazzo

# $* indica l’intera lista (stringa) dei parametri (non include il nome dello script)
# $# memorizza il numero di parametri (nome dello script escluso)
# $$ memorizza il PID del processo
echo "Please write 3 parameters (dir funct namefout):"
read dir funct fout

listOfFile=$(ls $dir -p | grep -v /)

for var in $listOfFile
do
	lines=$(egrep -n -H $funct $var)
	echo $lines 1>>/home/lillo/tmp.txt
done

sort -  1>/home/lillo/lab08es01Result.txt

exit 0
