#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<time.h>

#define N 100

void father(int p1[], int p2[]);
void child(int p1[], int p2[]);

int main(){

 int p1[2], p2[2];
 
 if(pipe(p1) < 0)
 	exit(1);
 if(pipe(p2) < 0)
 	exit(2);

  if(fork()==0)
  	child(p1, p2);
  else  {
  	father(p1, p2);
  	wait(NULL);
	}
	
 close(p1[0]);
 close(p1[1]);
 close(p2[0]);
 close(p2[1]);

 return 0;
}



void father(int p1[], int p2[]){

 char c='P';
 char tmp;
 pid_t pid= getpid();
 int bastaddu;
 
 srand(time(NULL));
  
 while(1){
 
 fprintf(stdout, "I'm the father with PID=%d\n", pid); 
 
 bastaddu=rand()%50;
 if(bastaddu>40){
 	 tmp='D';
 	 fprintf(stdout, "Azz sto bastaddu e == %d, chiudo tutto\n", bastaddu);
 	 write(p1[1], &tmp, sizeof(char));
 	 break;
 }
 
 write(p1[1], &c, sizeof(char));
 
 read(p2[0], &tmp, sizeof(char));
 }

 
}




void child(int p1[], int p2[]){
 
 char c='C';
 char tmp;
 pid_t pid= getpid();
  
 while(1){
 read(p1[0], &tmp, sizeof(char));
 	
 fprintf(stdout, "I'm the child with PID=%d\n", pid);
 if(tmp=='D'){
 	fprintf(stdout, "Azz papa' mi ha ammazzato, bastaddu!\n");
 	break;
 }
 
 
 write(p2[1], &c, sizeof(char));
 }
}
