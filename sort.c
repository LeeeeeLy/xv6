/*OS6611
  Assignment 1 Q2
  Xiaowen Li*/

/* SORT command is used to sort a file, arranging the records in a particular order. By default, the
sort command sorts file assuming the contents are ASCII. Using options in the sort command can
also be used to sort numerically.*/

/*options:
  -r: Sorting in reverse order
  -o: Write the output to a new file 
  -n: To sort a file numerically */

#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"

/*functions headers*/
int comp(char *str1,char *str2);/*compares two strings with >=<*/
void sortn(char *arr[], int n);/*sort by number(uses atoi)*/
void sorts(char *arr[], int n);/*sort by string(uses comp)*/

char buf[512];
char temp[512];



int 
comp(char *str1,char *str2){
  
  int i;
  int bo =-1;
  int len = strlen(str1);
  if(strcmp(str1,str2) == 0) 
    return 0;
  for(i = 0; i < len; i++){
    int a = (int) str1[i];
    int b = (int) str2[i];  
    if(a-b == 32 || b-a == 32){
        if(bo == -1)
            bo = a < b ? 1 : -1; 
    }
    else if (a-b != 0){
        if(a>=65 && a<97) a = a + 32;
        if(b>=65 && b<97) b = b + 32;
        bo = b < a ? 1 : -1; 
        break;
    }
  }
  return bo;
}

void 
sortn(char *arr[], int n){
  int i, j;
  char *tmp;

  for (i = 1; i < n; i++){
    tmp = arr[i];
    j = i - 1;
    while (j >= 0 && atoi(arr[j]) > atoi(tmp)){
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = tmp;
  }
 }
       
void 
sorts(char *arr[], int n){
  int i, j;
  int k;
  char temp2[512];

  for (i = 0; i < n-1; i++){
    k = i;
    strcpy(temp2, arr[i]);

    for (j = i+1; j < n; j++){
      if (comp(temp2, arr[j]) > 0){
        strcpy(temp2, arr[j]);
        k = j;
      }
    }

    if (k != i){
      strcpy(temp, arr[i]);
      strcpy(arr[i], arr[k]);
      strcpy(arr[k], temp);
    }
  }
}

void 
sort(int ifd, int ofd,int roption,int ooption,int noption){
  int i = 0;
  int j = 0;
  int k = 0;
  int n;

  

  char *txt[512];
  char *temp = (char *) malloc(512);

  while((n = read(ifd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      if(buf[i] != '\n'){
        temp[j++] = buf[i];
      }
      else{
        txt[k] = temp;
        temp = (char *) malloc(512);
        k++;

        j=0;
      }
    }
  }
  
  if(roption){ 
    if(noption)
      sortn(txt,k);   
    else
      sorts(txt,k);
    for(i = k-1 ; i >= 0 ; i--){
      if(write(ofd, txt[i], strlen(txt[i])) != strlen(txt[i]) || write(ofd, "\n", 1) != 1) {
        printf(2, "sort: write error\n");
        exit();
      }
    }
  }
  else{
    if(noption)
      sortn(txt,k);   
    else
      sorts(txt,k);
    for(i = 0 ; i < k ; i++){
      if(write(ofd, txt[i], strlen(txt[i])) != strlen(txt[i]) || write(ofd, "\n", 1) != 1) {
        printf(2, "sort: write error\n");
        exit();
      }
    } 
  }
}

int
main(int argc, char *argv[]){
  int fo;
  int fs = 0;
  int r = 0, o = 0, n = 0;

  int ut;
  ut = uptime();
  printf(1, "up %d ticks\n", ut);
  
  if(argc <= 1){
    printf(1,"Too less argument.\n");
  }
  if(argc == 2){      
    /*only filename*/ 
    if((fo = open(argv[1], 0)) < 0){
      printf(1, "sort: cannot open %s\n", argv[1]);
      exit();
    }
    sort(fo,fs,r,o,n);
    close(fo);
  }
  if(argc >= 3){
    /*has options*/
    if(argv[1][0] == '-'){
      switch(argv[1][1]){
        case 'r':
          r = 1;
          break;
        case 'o':
          o = 1;
          break;
        case 'n':
          n = 1;
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

    /*-o*/   
    if(o){
      if((fs = open(argv[2], O_CREATE | O_WRONLY)) < 0){
        printf(1, "cannot open output file %s\n", argv[2]);
        exit();
      }
      if((fo = open(argv[3], 0)) < 0){
        printf(1, "sort: cannot open %s\n", argv[2]);
        exit();
      }
      sort(fo,fs,r,o,n);
      close(fo);
      close(fs);
    }  
    /*not -o*/
    else{
      if((fo = open(argv[2], 0)) < 0){
      printf(1, "sort: cannot open %s\n", argv[2]);
      exit();
    }
    sort(fo,0,r,o,n);
    close(fo);  
    }
  }
  ut = uptime();
  printf(1, "up %d ticks\n", ut);
  exit();
}
