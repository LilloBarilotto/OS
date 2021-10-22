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

#define N 258

void ls_r(char* previous_path, struct stat * p_statbuf);


int main (	int argc, char *argv[]){

struct stat statbuf;  

if (argc != 2) {
    fprintf (stderr, "Usage: pgrm <pathname>");
    exit (1);
  }

  if (lstat(argv[1], &statbuf) < 0 ) {
    fprintf (stderr, "Error.\n");
    exit (1);
  }

  if (S_ISDIR(statbuf.st_mode) == 0) {
    fprintf (stderr, "Error.\n");
    exit (1);
  }

  ls_r(argv[1], &statbuf);
}

void ls_r(char* previous_path, struct stat * p_statbuf){	
  DIR *dp;
  char fullName[N];
  struct dirent *dirp;

  /* Directory */
  if ( (dp = opendir(previous_path)) == NULL) {
    fprintf (stderr, "Error.\n");
    exit (1);
  }

  while ( (dirp = readdir(dp)) != NULL) {
    sprintf (fullName, "%s/%s", previous_path, dirp->d_name);

    if (lstat(fullName, p_statbuf) < 0 ) {
      fprintf (stderr, "Error.\n");
      exit (1);
    }

    if (S_ISDIR(p_statbuf->st_mode) == 0) {
      fprintf (stdout, "File : %s\n", fullName);
    } else {
          fprintf (stdout, "Dir  : %s\n", fullName);
          
          if(strcmp(".",dirp->d_name)!=0 && strcmp("..", dirp->d_name)!=0){
            ls_r(fullName, p_statbuf);
          }
    }
  }

  if (closedir(dp) < 0) {
    fprintf (stderr, "Error.\n");
    exit (1);
  }

}


/*
Esercizio 01
Visualizzazione ricorsiva di un direttorio
------------------------------------------

Si scriva un programma in linguaggio C in grado di:
- ricevere sulla riga di comando il path (assoluto o relativo)
  di un albero di direttori
- visualizzare *ricorsivamente" il contenuto di tale albero (i.e.,
  tutti i file, i sotto-direttori, i file nei sotto-direttori,
  etc.).

Si compili in programma mediante gcc e ne si verifichi il
funzionamento confrontandone i risultati con il comando di
shell
"ls -R"

Suggerimenti
------------

- Scrivere una procedura ricorsiva che generalizzi la
  visualizzazione non ricorsiva di un direttorio analizzata
  a lezione
- Fare attenzione alla gestione dei path dei direttori/file
- Gestire esplicitamente i direttori
  "." e ".."
  per evitare ricorsioni infinite.
*/


/*

dirent.h

DIR *opendir(const char *filename); //apre direttorio in lettura
struct dirent *readdir( DIR * dp);  //leggi un file da direttorio, ritorna puntatore o  null se ho finito i file???


*/
