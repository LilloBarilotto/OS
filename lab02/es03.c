#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <unistd.h>


#include  <limits.h>
#include  <errno.h>
#include  <stdarg.h>

#include <fcntl.h>

#define N 258
#define BUFFSIZE 4096

void ls_r(char* previous_path, struct stat * p_statbuf, char* write_path);
void cp_file(char* fnamesource, char * fnamedest);

int main (int argc, char *argv[]){

struct stat statbuf;  

if (argc != 3) {
    fprintf (stderr, "Usage: pgrm <pathname>");
    exit (1);
  }

  if (lstat(argv[1], &statbuf) < 0 ) {
    fprintf (stderr, "Error.\n");
    exit (2);
  }

  if (S_ISDIR(statbuf.st_mode) == 0) {
    fprintf (stderr, "Error.\n");
    exit (3);
  }

  ls_r(argv[1] , &statbuf, argv[2]);
  
  return 0;
}

void ls_r(char* previous_path, struct stat * p_statbuf, char* write_path){	
  DIR *dp;
  char fullNamesource[N];
  char fullNamedest[N];
  struct dirent *dirp;


  if ( opendir(write_path) == NULL){
    mkdir(write_path, S_IRWXU | S_IRWXG | S_IRWXO);
  }

  /* Directory */
  if ( (dp = opendir(previous_path)) == NULL) {
    fprintf (stderr, "Error.\n");
    exit (4);
  }

  while ( (dirp = readdir(dp)) != NULL) {
    
    sprintf (fullNamesource, "%s/%s", previous_path, dirp->d_name);
    sprintf (fullNamedest, "%s/%s", write_path, dirp->d_name);
    fprintf(stdout, "%s\n", fullNamesource);

    if (lstat(fullNamesource, p_statbuf) < 0 ) {
      fprintf (stderr, "Error.\n");
      exit (2);
    }

    if (S_ISDIR(p_statbuf->st_mode) == 0) {
      cp_file(fullNamesource, fullNamedest);
    }else if(strcmp(".",dirp->d_name)!=0 && strcmp("..", dirp->d_name)!=0){
      ls_r(fullNamesource, p_statbuf, fullNamedest);
    }
    
  }

  if (closedir(dp) < 0) {
    fprintf (stderr, "Error.\n");
    exit (5);
  }

}

void cp_file(char* fnamesource, char * fnamedest){
  int fin, fout;
  int nR, nW;
  char buf[BUFFSIZE];

  if( (fin=open(fnamesource, O_RDONLY)) ==-1){
    exit(6);
  }

  if( (fout=open(fnamedest, O_RDWR | O_CREAT)) ==-1){
    exit(6);
  }

  while( (nR = read(fin, buf, nR)) > 0){
    nW= write(fout, buf, nR);
    
    if(nR!=nW){
      fprintf(stderr, "Aiut errore in scrittura file, letti %d, scritti %d\n", nR, nW);
    }
  }

  close(fin);
  close(fout);
}
/*

dirent.h

DIR *opendir(const char *filename); //apre direttorio in lettura
struct dirent *readdir( DIR * dp);  //leggi un file da direttorio, ritorna puntatore o  null se ho finito i file???


*/
