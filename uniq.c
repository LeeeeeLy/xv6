/*OS6611
  Assignment 1 Q1
  Xiaowen Li*/

/* uniq command in Linux is a command-line utility that reports or lters out the repeated lines
in a le. In simple words, uniq is the tool that helps to detect the adjacent duplicate lines and also
deletes the duplicate lines. uniq lters out the adjacent matching lines from the input le(that is
required as an argument) and writes the ltered data to the output le.*/

/*options:
  -c: count
  -i: ignore cases
  -d: repeat*/

#include "types.h"
#include "stat.h"
#include "user.h"

#define SIZE 1536


/*functions headers*/
void uniq(int fd, int coption, int ioption, int doption);
char tolower(unsigned char ch);/*required by strcmpnc*/
int strcmpnc(const char *p, const char *q);/*comaprison that case does not matter*/
int getline(int fd, char *buf, int len);
void inizarr(char *str, int size);

int 
getline(int fd, char *str, int len)
{
    char letter;
    int i = 0;
    int c;

    while(i++ < en)
    {
      c = read(fd, &letter, 1);/*read in*/
      if(c < 1)
        return -1;
      str[i] = letter;
      if(letter == '\n')
         break;
    }
    str[i] = '\0';/*add to the end*/
    return strlen(str);
}

void 
inizarr(char *str, int size)
{
    int i;

    for(i = 0; i < size; i++)
        str[i] = '\0';
}

char
tolower(unsigned char ch) {
    if (ch >= 'A' && ch <= 'Z')
        ch = 'a' + (ch - 'A');
    return ch;
}

int strcmpnc(const char * str1, const char * str2)
{
    int cpflag = 0;

    while ( *str1 || *str2)
    {
        cpflag = tolower((int)(*str1)) - tolower((int)(*str2));
        if (cpflag != 0)
        {
            break;
        }
        str1++;
        str2++;
    }

    return cpflag;
}

void
uniq(int fd, int coption, int ioption, int doption)
{
  char str1[SIZE], str2[SIZE];
  int count = 0;
  int flag = 0;
  
  inizarr(str2, SIZE);
  inizarr(str1, SIZE);

  if(coption){
    if(getline(fd, str1, SIZE) <= 0)
        return;
    strcpy(str2, str1);
    while(1)
    {
        while(strcmp(str1, str2) == 0)
        {
            inizarr(str1, SIZE);
            count++;
            if(getline(fd, str1, SIZE) <= 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag)
        {
            printf(1, "%d %s", count, str2);
            return;
        }
        printf(1, "%d %s", count, str2);
        count = 0;
        strcpy(str2, str1);
    }
  }
  else if(ioption){
    while(1)
    {
        inizarr(str1, SIZE);
        if(getline(fd, str1, SIZE) <= 0)
            return;
        while(strcmpnc(str1, str2) == 0)
        {
            inizarr(str1, SIZE);
            if(getline(fd, str1, SIZE) <= 0)
                return;
        }
        printf(1, "%s", str1);
        strcpy(str2, str1);
    }
  }
  else if(doption){
    while(1)
    {
        inizarr(str1, SIZE);
        if(getline(fd, str1, SIZE) <= 0)
            return;
        if(strcmp(str1, str2) != 0)
            strcpy(str2, str1);
        else
        {
            while(strcmp(str1, str2) == 0)
            {
                inizarr(str1, SIZE);
                if(getline(fd, str1, SIZE) <= 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
            {
                printf(1, "%s", str2);
                return;
            }
            printf(1, "%s", str2);
            strcpy(str2, str1);
        }
    }

  }
  else{
    while(1)
    {
        inizarr(str1, SIZE);
        if(getline(fd, str1, SIZE) <= 0)
            return;
        while(strcmp(str1, str2) == 0)
        {
            inizarr(str1, SIZE);
            if(getline(fd, str1, SIZE) <= 0)
                return;
        }
        printf(1, "%s", str1);
        strcpy(str2, str1);
    }
  }
}


int
main(int argc, char *argv[])
{
  int fd;
  int c = 0, i = 0, d = 0;

  if(argc <= 1){
    printf(1,"Too less argument.\n");
    exit();
  }
  if(argc == 2){
    /*only filename*/ 
    if((fd = open(argv[1], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[1]);
      exit();
    }
    printf(1,"Filename: %s\n", argv[1]);
    uniq(fd,c,i,d);
    close(fd);
  }
  if(argc == 3){
    /*has options*/
    if(argv[1][0] == '-')
      {
          switch(argv[1][1])
          {
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
    printf(1,"Filename: %s\n", argv[2]);
    uniq(fd,c,i,d);
    close(fd);  
  }
  if(argc > 3){
    printf(1, "uniq: too many arguments \n");
    exit();
  } 
  exit();
}
