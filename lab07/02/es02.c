#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>

#define MAXBUFF 100

struct tS {
 char *nfin;
 char *nfout;
};

int * readFile(FILE *fp, int * p_n); //this function read first line, take the first N, allocate an array with N elements
void order(int *v, int n);	 // reorder array with bubble sort, or maybe another sort idk I will choose soon... stay tuned | SPOILER: I take in prestito the prof sol of bubbleSort perché mi secca scriver codice dovevo fare il cuoco
void writeFile(FILE *fp, int * v, int n);// simple write of N elements 
void * ThreadTime(void * par);

int main(
 int argc,
 char * argv[]
)
{ 
 char buf[MAXBUFF];
 
 int i,n;

 pthread_t *t;
 struct tS *v;
 
 if(argc!=4){
 	fprintf(stderr, "Errore, sono stati passati in tot %d parametri e non 4 (3+NomeProgramma), mi spengo ciaone!\n", argc);
 	exit(1);
 }
 
 if( (n=atoi(argv[1]))<=0 ){
 	fprintf(stderr, "WTF BRO AGAIN, why negative number on my fucking program, why %d, come on!\n", n);
 	exit(2);
 };
 
 t=(pthread_t *) malloc(n*sizeof(pthread_t));
 v=(struct tS *) malloc(n*sizeof(struct tS));
 

 //Generation of n name of input and output
 for(i=0; i<n; i++){
 	sprintf(buf, "%s%d.txt", argv[2], i+1); 
 	v[i].nfin=strdup(buf);
 	
 	sprintf(buf, "%s%d.txt", argv[3], i+1); 
 	v[i].nfout=strdup(buf);
 }
 
 for(i=0; i<n; i++){
 	pthread_create (&t[i], NULL, ThreadTime, (void *)&v[i]);
 }
 
 //ATTESA DEI VARI THREAD
 for (i=0; i<n; i++) {
	pthread_join (t[i], NULL);
 }
 
 
 //FREE DI TUTTO QUELLO CHE HA BISOGNO DI ESSERE FREE
 for(i=0; i<n; i++){
 	free(v[i].nfin);
 	free(v[i].nfout);
 }
 free(t);
 free(v);
 
 return 0;
}


void * ThreadTime(void * par){

 FILE *fin;
 FILE *fout;
 int *v;
 int n;
 struct tS *tD;
 
 tD=(struct tS *)par;
 
 if( (fin=fopen(tD->nfin, "r"))==NULL){
 	fprintf(stderr, "PID:%d, T_ID:%lu, I cannot open input file '%s', bye..\n", getpid(), pthread_self(), tD->nfin);
 	exit(4);
 }
 
 if( (fout=fopen(tD->nfout, "w"))==NULL){
 	fprintf(stderr, "PID:%d, T_ID:%lu, I cannot open output file '%s', bye..\n", getpid(), pthread_self(), tD->nfout);
 	exit(4);
 }
 
 v=readFile(fin, &n);
 fclose(fin);
 
 order(v, n);
 
 writeFile(fout ,v, n);
 fclose(fout);
 
 free(v);
 
 pthread_exit((void*) NULL);
}


int * readFile(FILE *fp, int * p_n){
 int n;
 int *v;
 
 fscanf(fp, "%d", &n);
 (*p_n)=n;
 
 v=(int*) malloc(n* sizeof(int));
 
 for(int i=0; i<n; i++){
 	fscanf(fp, "%d", &v[i]);
 }
 
 return v;
}

void writeFile(FILE *fp, int * v, int n){

 for(int i=0; i<n; i++){
 	fprintf(fp, "%d\n", v[i]);
 }

}

void order(int *v, int n){
 int i,j, val;
 
 for (i=0; i<n-1; i++) {
  for (j=0; j<n-1-i; j++) {
    if (v[j] > v[j+1]) {
       val = v[j];
       v[j] = v[j+1];
       v[j+1] = val;
    }
  }
 }

}



/*
Realizzare un programma concorrente con N thread in grado di
ordinare dei file di ingresso, procedendo in parallelo sui
diversi file, secondo le seguenti specifiche.

Il programma (di nome pgrm) riceve 3 parametri sulla riga di
comando
pgrm n strA strB
dove:
- n e' un valore intero
- strA e' una stringa che identifica il nome di n file di
  ingresso, di nome
  strA1.txt, strA2.txt, ..., strAn.txt
- strB e' una stringa che identifica il nome di n file di
  uscita, di nome
  strB1.txt, strB2.txt, ..., strBn.txt

I file di ingresso strA contengono:
* sulla prima riga, il numero di interi memorizzati sulle
  righe successive alla prima
* sulle righe successive, tali interi.
Il seguente e' un esempio corretto di file:

5
102
99
34
234
25

Il programma, una volta generati gli n nomi dei due file di
ingresso e di uscita, attiva n thread.
Ciascun thread:
- legge dal "proprio" file di ingresso il vettore di interi
- ordina (con un algoritmo di ordinamento a scelta) tale
  vettore in ordine numerico crescente
- memorizza il risultato nel corrispondente file di uscita
  ("personale").

Si noti che il programma di fatto implementa il seguente
grafo di precedenza:

    Mi---------
    /\        |  
   /  \       |
  R1    R2   ...
  |     |
  O1    O2   ...
  |     |
  W1    W2   ...
   \  /
    \/        |
    Mf---------

In cui:
- Mi e Mf sono le operazioni iniziali e finali del main
- I flussi Ri, Oi e Wi sono le esecuzioni dei vari thread,
  ciascuno dei quali
  - legge il proprio file di ingresso, Ri
  - lo ordina, Oi
  - lo memorizza sul file di uscita, Wi.
  */
