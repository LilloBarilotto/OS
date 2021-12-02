#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>

#define N 100

void producer(int p[]);
void consumer(int p[]);

int main(){

 int p[2];
 
 if(pipe(p) < 0)
 	exit(1);
 	
  if(fork()==0)
  	consumer(p);
  else if(fork()==0)
  	producer(p);
  else{
  	close(p[0]);
  	close(p[1]);
  	wait(NULL);
  	wait(NULL);
  }

 return 0;
}

void producer(int p[]){

 int n;
 char buffer[N];

 close(p[0]);
 
 while(1){
 
 fscanf(stdin, "%s", buffer);
 n=strlen(buffer)+1;
 
 write(p[1], &n, sizeof(int));
 write(p[1], buffer, sizeof(char)*n);
 
 if(strcmp(buffer, "end")==0)
 	break;
 }
 
 close(p[1]);
}

void consumer(int p[]){
 
 int i, n;
 char buffer[N];
 
 close(p[1]);
 
 setbuf(stdout, 0);
 
 while(1){
 
 read(p[0], &n, sizeof(int));
 read(p[0], buffer, sizeof(char)*n);
 
 if(strcmp(buffer, "end")==0)
 	break;
 
 for(i=0; i<n; i++)
 	if(buffer[i]>='a' && buffer[i]<='z') buffer[i]=buffer[i]-32; 
 
 fprintf(stdout, "%s", buffer); 
 }
 
 close(p[0]);
}
