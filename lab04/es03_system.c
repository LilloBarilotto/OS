#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 200
#define C 40


int main(int argc, char*argv[]){

  FILE* fin;  
  char cmd[N];
  
  //tmp variable
  char see[C];
  int i=0;

  if(argc!=2)
  	return -1;
  	
  if( (fin=fopen(argv[1], "r")) == NULL){
    exit(6);
  }
  
  while( fscanf(fin, "%s", see)!= EOF){
  	if(strcmp(see, "end")==0){
		system(cmd);
		cmd[0]='\0';
  	}	
  	else{
  		strcat(cmd, " ");
  		strcat(cmd, see);  		
  	}
  }
  
  fclose(fin);
  return 0;
}
