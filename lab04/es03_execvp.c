#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define K 200

void freeMOD(char** argv, int n);
void addArgvSend(char *** argv, char*  buffer, int* i, int* N);

int main(int argc, char*argv[]){

  FILE* fin;  
  
  char** argvSEND;
  int i=0;
  int N=4;
  
  char buffer[K];

  if(argc!=2)
  	return -1;
  	
  if( (fin=fopen(argv[1], "r")) == NULL){
    exit(6);
  }
  
  argvSEND= malloc(N* sizeof(char *));
  
  while( fscanf(fin, "%s", buffer)!= EOF){
  	if(strcmp(buffer, "end")==0){
  		
  		if(fork()==0){
  			execvp(argvSEND[0] , (argvSEND+ sizeof(char *)));
  		}
  		else{  //else evitabile
  			sleep(4);
  			freeMOD(argvSEND, i);
  	
  			i=0;
  			N=4;
  			argvSEND= malloc(N* sizeof(char *));
  		}
  	}	
  	else{
  		addArgvSend(&argvSEND, buffer, &i, &N);
  	}
  }
  
  freeMOD(argvSEND, i);
  
  fclose(fin);
  return 0;
}


void freeMOD(char** argv, int n){
	int i;
	for(i=0; i<n; i++)
		free(argv[i]);
		
	free(argv);
}

void addArgvSend(char *** argv, char*  buffer, int* i, int* N){
		
	(*argv)[*i]=strdup(buffer);
	*i= *i+1;
	
	if( *i>= *N){
		*N= 2*(*N);
		(*argv)=realloc(*argv, (*N)*sizeof(char *) );
	}			
}
