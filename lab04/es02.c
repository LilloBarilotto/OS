#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
  int i = 0;
  char stampastrana[100];
  
  
  setbuf(stdout,0);
  while (i<=2 && fork()){
    if (!fork()) {
      fprintf (stdout, "Running Exec ...");
      sprintf(stampastrana, "i*i PID:%d, PPID%d", getpid(), getppid());
      execlp ("echo", "echo", stampastrana, (char *) 0);
    }
    i++;
    fprintf (stdout, "Running System ...");
    sprintf(stampastrana, "echo i+i PID:%d, PPID%d", getpid(), getppid());
    system (stampastrana);
  }

  return (0);
} 

