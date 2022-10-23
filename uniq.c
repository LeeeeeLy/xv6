/*OS6611
  Assignment 1 Q1
  Xiaowen Li*/

/* uniq command in Linux is a command-line utility that reports or lters out the repeated lines
in a le. In simple words, uniq is the tool that helps to detect the adjacent duplicate lines and also
deletes the duplicate lines. uniq filters out the adjacent matching lines from the input file(that is
required as an argument) and writes the filtered data to the output file.*/

/*options:
  -c: count
  -i: ignore cases
  -d: repeat*/

#include "types.h"
#include "stat.h"
#include "user.h"


/*functions headers*/
void uniq(int fd, int coption, int ioption, int doption);/*main uniq function, has option c,i,d, and none*/
char tolower(unsigned char ch);/*required by strcmpnc*/
int strcmpnc(const char *p, const char *q);/*comaprison that case does not matter*/
int getline(int fd, char *buf);/*get line*/
void inizarr(char *str);/*initialize the array with given size*/

int 
getline(int fd, char *buf){
  int i, ro;
  int len = 512;
  char letter;

  for(i = 0; i + 1 < len;){
    ro = read(fd, &letter, 1);/*read in*/
    if(ro < 1)
      return -1;
    buf[i++] = letter;
    if(letter == '\n')
      break;
  }
  buf[i] = '\0';/*add to the end*/
  return strlen(buf);
}

void 
inizarr(char *str){
  int i;
  int size = 512;

  for(i = 0; i < size; i++)
    str[i] = '\0';
}

char
tolower(unsigned char ch){
  if (ch >= 'A' && ch <= 'Z')
    ch = 'a' + (ch - 'A');
  return ch;
}

int strcmpnc(const char * str1, const char * str2){
  int cpflag = 0;

  while ( *str1 || *str2){
    cpflag = tolower((int)(*str1)) - tolower((int)(*str2));
    if (cpflag != 0){
      break;
    }
    str1++;
    str2++;
  }

  return cpflag;
}

void
uniq(int fd, int coption, int ioption, int doption){
  char str1[512], str2[512];
  int count = 0;
  int flag = 0;
  
  inizarr(str2);
  inizarr(str1);

  if(coption){
    if(getline(fd, str1) <= 0)
      return;
    strcpy(str2, str1);
    while(1){
      while(strcmp(str1, str2) == 0){
        inizarr(str1);
        count++;
        if(getline(fd, str1) <= 0){
          flag = 1;
          break;
        }
      }
      if(flag){/*last one*/
        printf(1, "%d %s", count, str2);
        return;
      }
      printf(1, "%d %s", count, str2);
      count = 0;
      strcpy(str2, str1);
    }
  }
  else if(ioption){
    while(1){
      inizarr(str1);
      if(getline(fd, str1) <= 0)
          return;
      while(strcmpnc(str1, str2) == 0){
        inizarr(str1);
        if(getline(fd, str1) <= 0)
          return;
      }
      printf(1, "%s", str1);
      strcpy(str2, str1);
    }
  }
  else if(doption){
    while(1){
      inizarr(str1);
      if(getline(fd, str1) <= 0)
        return;
      if(strcmp(str1, str2) != 0)
        strcpy(str2, str1);
      else{
        while(strcmp(str1, str2) == 0){
          inizarr(str1);
          if(getline(fd, str1) <= 0){
            flag = 1;
            break;
          }
        }
        if(flag){
          printf(1, "%s", str2);
          return;
        }
        printf(1, "%s", str2);
        strcpy(str2, str1);
      }
    }

  }
  else{
    while(1){
      inizarr(str1);
      if(getline(fd, str1) <= 0)
        return;
      while(strcmp(str1, str2) == 0){
        inizarr(str1);
        if(getline(fd, str1) <= 0)
          return;
      }
      printf(1, "%s", str1);
      strcpy(str2, str1);
    }
  }
}


int
main(int argc, char *argv[]){
  int fd;
  int c = 0, i = 0, d = 0;
  int ut;
	ut = uptime();
	printf(1, "up %d ticks\n", ut);

  if(argc <= 1){
    //printf(1,"Too less argument.\n");
    uniq(0,c,i,d);/*so that it can take input from pipe*/
  }
  if(argc == 2){
    /*with pipe*/
    if(argv[1][0] == '-'){
      switch(argv[1][1]){
        case 'i':
          i = 1;
          break;
        case 'd':
          d = 1;
          break;
        case 'c':
          c = 1;
          break;
        default:
          printf(1,"Option not suppoted.\n");
          exit();
      }
      uniq(0,c,i,d);
    }
      
    /*only filename*/ 
    if((fd = open(argv[1], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[1]);
      exit();
    }
    uniq(fd,c,i,d);
    close(fd);
  }
  if(argc == 3){
    /*has options*/
    if(argv[1][0] == '-'){
      switch(argv[1][1]){
        case 'i':
          i = 1;
          break;
        case 'd':
          d = 1;
          break;
        case 'c':
          c = 1;
          break;
        default:
          printf(1,"Option not suppoted.\n");
          exit();
      }
    }
    else{
      printf(1,"Two arguments were received, the option must goes front of the filename, the option should start with '-'.\n");
      exit();
    }
            
    if((fd = open(argv[2], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[2]);
      exit();
    }
    uniq(fd,c,i,d);
    close(fd);  
  }
  if(argc > 3){
    printf(1, "uniq: too many arguments \n");
    exit();
  } 
  ut = uptime();
	printf(1, "up %d ticks\n", ut);
  exit();
}
