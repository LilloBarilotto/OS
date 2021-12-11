#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#define N 8
//I thread sono 9, solo che I non muore e fa da ciclo anche per gli altri

sem_t *BCD, *EF, *G, *H, *I, *A;

void * pA(void *par){
	sem_wait(A);
	
	printf("A\n");
	sleep(5);
	
	sem_post(BCD);
	sem_post(BCD);
	sem_post(BCD);
	
	pthread_exit((void*) NULL);
}

//tratto a sx B
void * pB(void *par){
	sem_wait(BCD);
	
	printf("B\n");
	
	sem_post(I);

 	pthread_exit((void*) NULL);
}

//tratto centrale C->E,F->G
void * pC(void *par){
	sem_wait(BCD);
	
	printf("C\n");
	
	sem_post(EF);
	sem_post(EF);

 	pthread_exit((void*) NULL);
}

void * pE(void *par){
	sem_wait(EF);
	
	printf("E\n");
	
	sem_post(G);

 	pthread_exit((void*) NULL);
}

void * pF(void *par){
	sem_wait(EF);
	
	printf("F\n");
	
	sem_post(G);

 	pthread_exit((void*) NULL);
}

void * pG(void *par){
	sem_wait(G);
	sem_wait(G);
	
	printf("G\n");
	
	sem_post(I);

 	pthread_exit((void*) NULL);
}

//tratto dx D->H
void * pD(void *par){
	sem_wait(BCD);
	
	printf("D\n");
	
	sem_post(H);
	
 	pthread_exit((void*) NULL);
}

void * pH(void *par){
	sem_wait(H);
	
	printf("H\n");
	
	sem_post(I);
	
 	pthread_exit((void*) NULL);
}

//ritorno ad A da I
void pI(void *par){
	sem_wait(I);
	sem_wait(I);
	sem_wait(I);
	
	printf("I\n\n\n");
	sem_post(A);
}

int main(){
 int i=0;
 pthread_t *t;
 
 BCD=(sem_t *) malloc(sizeof(sem_t));
 EF=(sem_t *) malloc(sizeof(sem_t));
 G=(sem_t *) malloc(sizeof(sem_t));
 H=(sem_t *) malloc(sizeof(sem_t));
 I=(sem_t *) malloc(sizeof(sem_t));
 A=(sem_t *) malloc(sizeof(sem_t));
 
 sem_init(BCD,0,0);
 sem_init(EF,0,0);
 sem_init(G,0,0);
 sem_init(H,0,0);
 sem_init(I,0,0);
 sem_init(A,0,1);
 
 t=(pthread_t *) malloc(N*sizeof(pthread_t));
 
 for(i=0; i<5; i++){
 	
 	pthread_create(&t[0],NULL,pA,NULL);
  	pthread_create(&t[1],NULL,pB,NULL);
   	pthread_create(&t[2],NULL,pC,NULL);
    	pthread_create(&t[3],NULL,pD,NULL);
     	pthread_create(&t[4],NULL,pE,NULL);
      	pthread_create(&t[5],NULL,pF,NULL);
       	pthread_create(&t[6],NULL,pG,NULL);
    	pthread_create(&t[7],NULL,pH,NULL);
 	pI(NULL);		
 }

 sem_destroy(BCD);
 sem_destroy(EF);
 sem_destroy(G);
 sem_destroy(H);
 sem_destroy(I);
 sem_destroy(A);

return 0;
}
