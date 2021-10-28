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

int main(int argc, char* argv[]){

 int n, t, i, pippo;
  
 if(argc!=3){
	printf("WTF BRO use 3 arguments..\n");
	return 1;
 }
 
 n= atoi(argv[1]);
 t= atoi(argv[2]);


 for(i=1; i<=n; i++){
 	if(fork()){
 		if(fork()){
 			break;
 		}
 	}
 }
 
 if(i>n){
 	sleep(t);
 	printf("BRO close the eyes... I'm process with PID:%d and PPID:%d.. I'm a leaf of level %d... Bye bro .-.\n", getpid(), getppid(), i-1); 
 }

return 0;
}
