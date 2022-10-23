#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  int pid;
  int k, n;
  int x, z;


  n = 5;

  for ( k = 0; k < n; k++ ) {
    pid = fork ();
    if ( pid < 0 ) {
      printf(1, "%d failed in fork!\n", getpid());
      exit();
    } else if (pid == 0) {
      // child
      printf(1, "Child %d created\n",getpid());
      for ( z = 0; z < 10000.0; z += 0.01 )
         x =  x + 3.14 * 89.64;   // useless calculations to consume CPU time
      exit();
    }
  }

  for (k = 0; k < n; k++) {
    wait();
  }

  exit();
}