/*OS6611
  Assignment 1 Q3
  Xiaowen Li*/

/* It is the complementary of Tail command. e head command, as the name implies, print the top
N number of data of the given input. By default, it prints the rst 10 lines of the specied les.
If more than one le name is provided then data from each le is preceded by its le name. If no
lename is provided, head should read from standard input.You should also be able to invoke it
without a le, and have it read from standard input*/
/*options:
  -n: lines*/

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

int aatoi(char *str){
    int i = 0;
    int val = 0;

    while(str[i] >= '0' && str[i] <= '9'){
        int nbr = (int) (str[i] - '0');
        val = (val * 10) + nbr;
        i++;
    }
    return (val);
}

void
head(int fd, int line){
    int i, n; 
    int j = 0; 


  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i = 0; i < n ; i++){				
      if(buf[i] != '\n'){			
      	printf(1,"%c",buf[i]);
      }			
      else{
      	printf(1,"\n");
      	j++;
        if(j == line){
            exit();
        }
      } 
    }
  }
  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}



int 
main(int argc, char *argv[]){
    int fd, nl;
    int nf; 

    if (argc <= 1){	
        head(0, 10);	
        exit();
    }
    if (argc >= 2){
        /*has options*/
        if(argv[1][0] == '-'){
            switch(argv[1][1]){
                case 'n':
                nl = aatoi(argv[2]);
                break;
                default:
                printf(1,"Option not suppoted.\n");
                exit();
            }
            
            for (nf = 3; nf<argc; nf++){
                if((fd = open(argv[nf], 0)) < 0){
                    printf(1, "uniq: cannot open %s\n", argv[nf]);
                    nf++;
                    close(fd);
                }
                printf(1,"==> %s <==\n", argv[nf]);
                head(fd,nl);
                close(fd);

            }
        }
        else{
            nl = 10;
            for (nf = 1; nf<argc; nf++){
                if((fd = open(argv[nf], 0)) < 0){
                    printf(1, "uniq: cannot open %s\n", argv[nf]);
                    nf++;
                    close(fd);
                }
                printf(1,"==> %s <==\n", argv[nf]);
                head(fd,nl);
                close(fd);

            }
        }
    }
    exit();
}

