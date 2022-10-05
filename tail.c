/*OS6611
  Assignment 2 Q2
  Xiaowen Li*/

/* It is the complementary of Head command. The Tail command, as the name implies, prints the
last N number of data of the given input. By default, it prints the last 10 lines of the specified
les. If more than one file name is provided then data from each file is preceded by its file name.
If no filename is provided, tail should read from standard input.You should also be able to invoke
it without a file, and have it read from standard input.*/
/*options:
  -n: lines*/

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


/*functions headers*/
void tail(char *fn, int line);


char buf[512];


void
tail(char *fn, int line){

  int i,n;
  int fd;
  int row = 0;

  if((fd = open(fn, 0)) < 0){
    printf(1, "tail: cannot open %s\n", fn);
    close(fd);
    exit();
  }
  
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i = 0; i < n ; i++){				
      if(buf[i] == '\n'){			
        row++;
        //printf(1, "%d", i);
      }			
    }
  }
  if(n < 0){
    printf(1, "tail: read error\n");
    close(fd);
    exit();
  }
  
  //printf(1, "number of rows: %d\n", row);

  close(fd);
  fd = open(fn, 0);
  
  int r = 0;
 // printf(1, "n: %d\n", n);
  //printf(1, "size of buf: %d\n", sizeof(buf));
  while((n = read(fd, buf, sizeof(buf))) > 0){
   // printf(1, "n: %d\n", n);
   // printf(1, "size of buf: %d\n", sizeof(buf));
    for(i = 0; i < n ; i++){				
      if(row-r <= line){			
      //  printf(1, " %d", i);
        printf(1, "%c", buf[i]);
      }			
      if(buf[i] == '\n'){
        //printf(1,"\n");
      	r++;
      }
    }
  }

  if(n < 0){
    printf(1, "tail: read error\n");
    exit();
  }

}

/*instead of directly pass fd to function, we pass the filename, due to the function tail need to open the*/

int 
main(int argc, char *argv[]){
    int nl;
    int nf; 

    if (argc <= 1){	
        tail(0, 10);	
        exit();
    }
    if (argc >= 2){
        /*has options*/
        if(argv[1][0] == '-'){
            switch(argv[1][1]){
                case 'n':
                nl = atoi(argv[2]);
                break;
                default:
                printf(1,"Option not suppoted.\n");
                exit();
            }

          for (nf = 3; nf<argc; nf++){   
            printf(1,"==> %s <==\n", argv[nf]);
            tail(argv[nf],nl);
          }
            
            /*for (nf = 3; nf<argc; nf++){
                if((fd = open(argv[nf], 0)) < 0){
                    printf(1, "tail: cannot open %s\n", argv[nf]);
                    nf++;
                    close(fd);
                }
                printf(1,"==> %s <==\n", argv[nf]);
                tail(fd,nl);
                close(fd);

            }*/
        }
        else{
          nl = 10;
          /*for (nf = 1; nf<argc; nf++){
              if((fd = open(argv[nf], 0)) < 0){
                  printf(1, "tail: cannot open %s\n", argv[nf]);
                  nf++;
                  close(fd);
              }
              printf(1,"==> %s <==\n", argv[nf]);
              tail(fd,nl);
              close(fd);

          }*/
          for (nf = 1; nf<argc; nf++){
          printf(1,"==> %s <==\n", argv[nf]);
          tail(argv[nf],nl);
          }
        }
    }
    exit();
}

