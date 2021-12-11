#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int BCD[2], EF[2], G[2], H[2], I[2], A[2];  

void semaphoreInit (int *S) {
  if (pipe (S) == -1) {
    printf("Error");
    exit (-1); 
  }
  return;
}

void semaphoreSignal (int *S) {
  char ctr = 'X';
  if (write(S[1], &ctr, sizeof(char)) != 1) {
    printf("Error");
    exit (-1);
  }
  return;
}

void semaphoreWait (int *S) {
  char ctr;
  if (read (S[0], &ctr, sizeof(char)) != 1) {
    printf("Error");
    exit (-1);
  }
  return;
}



void pA(){
	semaphoreWait(A);
	
	printf("A\n");
	//sleep(7);
	
	semaphoreSignal(BCD);
	semaphoreSignal(BCD);
	semaphoreSignal(BCD);
	
	exit(0);
}

//tratto a sx B
void pB(){
	semaphoreWait(BCD);
	
	printf("B\n");
	
	semaphoreSignal(I);

	exit(0);
}

//tratto centrale C->E,F->G
void pC(){
	semaphoreWait(BCD);
	
	printf("C\n");
	
	semaphoreSignal(EF);
	semaphoreSignal(EF);

	exit(0);
}

void pE(){
	semaphoreWait(EF);
	
	printf("E\n");
	
	semaphoreSignal(G);

	exit(0);
}

void pF(){
	semaphoreWait(EF);
	
	printf("F\n");
	
	semaphoreSignal(G);

	exit(0);
}

void pG(){
	semaphoreWait(G);
	semaphoreWait(G);
	
	printf("G\n");
	
	semaphoreSignal(I);

	exit(0);
}

//tratto dx D->H
void pD(){
	semaphoreWait(BCD);
	
	printf("D\n");
	
	semaphoreSignal(H);
	
	exit(0);
}

void pH(){
	semaphoreWait(H);
	
	printf("H\n");
	
	semaphoreSignal(I);
	
	exit(0);
}

//ritorno ad A da I
void pI(){
	semaphoreWait(I);
	semaphoreWait(I);
	semaphoreWait(I);
	
	printf("I\n");
	
	semaphoreSignal(A);
}

int main(){
 
 semaphoreInit(BCD);
 semaphoreInit(EF);
 semaphoreInit(G);
 semaphoreInit(H);
 semaphoreInit(I);
 semaphoreInit(A); 
 
 semaphoreSignal(A);
 
 while(1){
 	
 	if(fork()==0)
 		pA();
 	else if(fork()==0)
 		pB();
 	else if(fork()==0)
 		pC();
 	else if(fork()==0)
 		pD();
 	else if(fork()==0)
 		pE();
 	else if(fork()==0)
 		pF();
 	else if(fork()==0)
 		pG();
 	else if(fork()==0)
 		pH();
 	else 
 		pI();		
}

return 0;
}
