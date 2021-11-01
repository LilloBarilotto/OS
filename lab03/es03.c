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
#include <sys/wait.h>


int main(){

  printf("P1 %d\n", getpid());;

  if( fork() ){
  	printf("P2 %d\n", getpid());
  	
  	if( fork() ){
		printf("P4 %d\n", getpid());
		//waitpid...
  	}
  	else{
  		printf("P5 %d\n", getpid());
  		exit(0);
  	}
  	wait(NULL);
  	
  	printf("P7 %d\n", getpid());
  	wait(NULL);
  	//waitpid(pid);
  }
  else{
  	//P3
  	printf("P3 %d\n", getpid());
  	
  	if( !fork() ){
  		printf("P6 %d\n", getpid());
  		exit(0);
  	}
  	wait(NULL);
  	
  	printf("P8 %d\n", getpid());;
  	exit(0);
  }
  
  printf("P9 %d\n", getpid());
  
  return 0;
}
