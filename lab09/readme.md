ES 1, non ho ancora capito che se deve fa ma vbb  
  
ES 4, mi pare giusto concettualmente, ma c'è un problema con la stampa e la precedenza, in particolare tra E-F.  
Stampa in terminale:  
"lillo@pop-os:~/Desktop/lab09$ ./es04  
A
B
D
C
H
E
F
G
I
  

A
B
D
C
H
E
F
G
I
  

A
B
C
D
F
F
H
G
I
  
  
A
B
D
C
H
F
E
G
I
  

A
B
D
H
C
E
E
G
I"
  
Come si può vedere in 2 stampe sembra che F sia riuscito a "rubare" un signal a E, nella stampa 2 si vede "FF"  e in 4 "EE", sembrerebbe che F (o E) riesca a fare 2 cicli e 2 wait soddisfandoli entrambi prima che entri in gioco F.
