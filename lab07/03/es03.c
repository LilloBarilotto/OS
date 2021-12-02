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
 int *v;
 int n;
 int * ret;
};

void readFile(FILE *fp, int * v, int n);//this function read first line, take the first N, allocate an array with N elements
void writeFile(FILE *fp, int * v, int n);// simple write of N elements 
void * ThreadTime(void * par);


void MergeSortR(int * A, int * B, int l, int r);
void Merge(int *A, int *B, int l, int q, int r);
void order(int *v, int n);	 // reorder array with bubble sort, or maybe another sort idk I will choose soon... stay tuned | SPOILER: I take in prestito the prof sol of bubbleSort perché mi secca scriver codice dovevo fare il cuoco



int main(
 int argc,
 char * argv[]
)
{ 
 char buf[MAXBUFF];
 
 int n,cnt,i,j,k;

 pthread_t *t;
 struct tS *v;
 int* retV;
 
 int* finalVett;
 int* tmpVett;
 
 FILE *fout;
 
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
 retV=(int *)	 malloc(n*sizeof(int));
 
 finalVett=malloc(n*n*sizeof(int));
 tmpVett=malloc(n*n*sizeof(int));

 //Generation of n name of input and output
 for(i=0; i<n; i++){
 	sprintf(buf, "%s%d.txt", argv[2], i+1); 
 	v[i].nfin=strdup(buf);

 	v[i].v=(int *) malloc(n* sizeof(int));
 	v[i].n=n;
 	v[i].ret=&retV[i];
 }
 
 for(i=0; i<n; i++){
 	pthread_create (&t[i], NULL, ThreadTime, (void *)&v[i]);
 }
 
 //ATTESA DEI VARI THREAD
 cnt=0;
 while(cnt<n){
 	usleep(500);
 	
 	for(i=0;i<n; i++){
 		if(retV[i]==1){
 			//MERGE THE n value of this array 
 			
 			for(j=cnt*n, k=0; k<n; k++, j++){
 				finalVett[j]=v[i].v[k];
 			}
 			cnt++;
 			
 			MergeSortR(finalVett, tmpVett, 0, (cnt*n)-1); 
 			
 			retV[i]=0;
 		}
 	
 	}
 }
 
 if( (fout=fopen(argv[3], "w"))==NULL){
 	fprintf(stderr, "PID:%d, I cannot open output file '%s', bye..\n", getpid(), argv[3]);
 	exit(4);
 }
 
 writeFile(fout, finalVett, n*n);
 fclose(fout);
 
 //FREE DI TUTTO QUELLO CHE HA BISOGNO DI ESSERE FREE
 for(i=0; i<n; i++){
 	free(v[i].nfin);
 	free(v[i].v);
 }
 free(t);
 free(v);
 
 free(retV);
 free(tmpVett);
 free(finalVett);
 
 return 0;
}


void * ThreadTime(void * par){

 FILE *fin;
 struct tS *tD;
 
 tD=(struct tS *)par;
 
 if( (fin=fopen(tD->nfin, "r"))==NULL){
 	fprintf(stderr, "PID:%d, T_ID:%lu, I cannot open input file '%s', bye..\n", getpid(), pthread_self(), tD->nfin);
 	exit(4);
 }
 
 readFile(fin, tD->v, tD->n);
 fclose(fin);
 
 order(tD->v, tD->n);
 (*tD->ret)=1;
 
 pthread_exit((void*) NULL);
}


void readFile(FILE *fp, int * v, int n){
 for(int i=0; i<n; i++){
 	fscanf(fp, "%d", &v[i]);
 }
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

void MergeSortR(int * A, int * B, int l, int r){
    int q = (l + r)/2;
    if (r <= l)
        return;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
}

void Merge(int *A, int *B, int l, int q, int r){
    int i, j, k;
    i = l;
    j = q+1;

    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r || A[j]>A[i])
            B[k] = A[i++];
        else
            B[k] = A[j++];
            
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}
