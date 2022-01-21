/*
  Scrivere un programma in linguaggio C che, utilizzando le primitive
  di I/O ANSI C (fgetc/fputc, fscanf/fprint, fget/fputs a scelta), sia
  in grado di copiare un file di testo in file identico.
  Il nome due file sia ricevuto sulla riga di comando, in modo che
  il programma possa essere eseguito mediante un comando che specifica
  tre parametri:
  nomeEseguibile fileSorgente fileDestinazione
  
  Parte 04
  Modificare il programma utilizzando
  - le funzioni ANSI C fread e fwrite (opzionale)
  e quindi
  - le system call POSIX open, read, write e close.
  Provarne il corretto funzionamento mediante diff.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define N 1024

int main(int argc, char * argv[]){
 
 int fs, fd, neff;
 char buffer[N];
 
 if( argc!=3 ){
 	//Wrong usage, usage is: es04_v1 fileSource fileDest	
 	fprintf(stderr,"1");
 	exit(1);
 }
 
 if( (fs=open(argv[1], O_RDONLY))==-1){
 	// file source not found
 	fprintf(stderr,"2");
 	exit(2);
 }
 
 if( (fd=open(argv[2], O_WRONLY | O_CREAT , 0644))==-1){
 	// Problem with the number inode or something with the memory, idk broski your problem not mine.
 	fprintf(stderr,"3");
 	exit(3);
 }
 
 while( (neff=read(fs, buffer, sizeof(char)*N ))!=0){
 	write(fd, buffer, sizeof(char)*neff);
 }
 
 close(fs);
 close(fd);

 return 0;
}
