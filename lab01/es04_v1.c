/*
  Scrivere un programma in linguaggio C che, utilizzando le primitive
  di I/O ANSI C (fgetc/fputc, fscanf/fprint, fget/fputs a scelta), sia
  in grado di copiare un file di testo in file identico.
  Il nome due file sia ricevuto sulla riga di comando, in modo che
  il programma possa essere eseguito mediante un comando che specifica
  tre parametri:
  nomeEseguibile fileSorgente fileDestinazione
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define N 1024

int main(int argc, char * argv[]){
 
 FILE *fs, *fd;
 char buffer[N];
 
 if( argc!=3 ){
 	//Wrong usage, usage is: es04_v1 fileSource fileDest	
 	exit(1);
 }
 
 if( (fs=fopen(argv[1], "r"))==NULL){
 	// file source not found
 	exit(2);
 }
 
 if( (fd=fopen(argv[2], "w"))==NULL){
 	// Problem with the number inode or something with the memory, idk broski your problem not mine.
 	exit(3);
 }
 
 while( fgets(buffer, N, fs)!=NULL){
 	fputs(buffer, fd);
 }
 
 fclose(fs);
 fclose(fd);

 return 0;
}
