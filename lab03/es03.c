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

  //P1
  printf("P1\n");

  if( fork() ){
  	//P2
  	printf("P2\n");
  	
  	if( fork() ){
  		//P4
  		sleep(10);
		printf("P4\n");
		//waitpid...
  	}
  	else{
  		//P5
  		sleep(15);
  		printf("P5\n");
  		exit(0);
  	}
	sleep(20);
  	wait(NULL);
  	
  	//P7
  	printf("P7\n");
  	sleep(12);
  	wait(NULL);
  	//waitpid(pid);
  }
  else{
  	sleep(5);
  	//P3
  	printf("P3\n");
  	
  	if( !fork() ){
  		sleep(20);
  		//P6
  		printf("P6\n");
  		exit(0);
  	}
  	sleep(20);
  	wait(NULL);
  	
  	//P8
  	sleep(10);
  	printf("P8\n");
  	exit(0);
  }
  
  //P9
  printf("P9\n");
  
  return 0;
}
