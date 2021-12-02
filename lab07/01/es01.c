#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void binary(int *, int, int);

int
main (
  int argc,
  char *argv[]
  )
{
  int n;
  int *vet;

  n = atoi (argv[1]);

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL) {
    printf("Allocatin Error.\n");
    exit(1);
  }

  printf("Binary Numbers:\n");
  binary(vet, n, 0);
  free(vet);

  return 0;
}

void
binary (
  int *vet,
  int n,
  int i
  )
{
  int j;
  
  for(i=0; i<=n; i++){
  
	  if (i == n) {
	    for (j=0; j<n; j++) {
	      printf("%d", vet[j]);
	    }
	    printf("\n");
	    exit(0);
	  }

	  if(fork()==0){
	  	//1
	  	vet[i] = 0;
	  }
	  else if (fork()==0){
	  	//2
	  	vet[i] = 1;
	  }
	  else{
	  	//FATHER WAIT
	  	wait(NULL);
	  	wait(NULL);
	  	exit(0);
  	  } 
  }
}
