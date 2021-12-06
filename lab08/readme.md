LAB 8  
Es1 Versione For  
Letteralmente il file che mi crea è strano, in pratica, essendo più file, la grep su un solo file mi scrive tutte le indicazioni delle righe di quel file, su una riga finale soltanto.  
Vorrei capire quindi se attraverso la grep è possibile aggiungere uno \n ad ognuna delle righe.  

Es2  
Provando a far partire lo script da i seguenti errori:  
"lillo@pop-os:~/Desktop/lab08$ bash es02.sh  
Please write the name of the file:   
prova.txt  
es02.sh: line 18: 4: command not found  
es02.sh: line 18: 6: command not found  
es02.sh: line 18: 6: command not found  
es02.sh: line 18: 9: command not found  
es02.sh: line 18: 20: command not found  
es02.sh: line 18: 11: command not found  
es02.sh: line 18: 24: command not found  
es02.sh: line 18: 24: command not found  
es02.sh: line 18: 22: command not found  
es02.sh: line 18: 11: command not found  
es02.sh: line 18: 31: command not found  
NumberLIne= 11 prova.txt, MaxNumberChar= 0"  
Non capisco cosa ci sia di sbagliato nell'if..
