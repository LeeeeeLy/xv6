/*OS6611
  Assignment -1 
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

void sorts_selection(char *arr[], int n, int e);/*sort by string(uses comp)*/
void sortb(char *arr[], int n);/*ignore blanks*/
int sortu(char *arr[], int n);/*delete same lines*/
int strcmpnc(const char * str1, const char * str2);/*comparison that case does not matter*/
void sortM(char *arr[], int n);/*sort by month*/
int ft_atoi(char *str);
char buf[512];
char temp[512];
#define KONG NULL;


int ft_atoi(char *str){
    int i = 0;
    int sign = 1;
    int val = 0;

    while (str[i] == '-') {
        sign = -sign;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9'){
        int nbr = (int) (str[i] - '0');
        val = (val * 10) + nbr;
        i++;
    }
    return (val * sign);
}


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
  int k;
  char temp2[512];

  for (i = 0; i < n-1; i++){
    k = i;
    //strcpy(temp2, arr[k]);

    for (j = i+1; j < n; j++){
      if (ft_atoi(arr[k])>ft_atoi(arr[j])){
        //strcpy(temp2, arr[j]);
        k = j;
      }
    }

    if (k != i){
      strcpy(temp2, arr[i]);
      strcpy(arr[i], arr[k]);
      strcpy(arr[k], temp2);
    }
  }
}



void 
sortb(char *arr[], int n){
  //printf(1, "in sortb!\n");
  int i, offset;
  char *tmp;

  for (i = 0; i < n; i++) {
    offset = 0;
    tmp = arr[i];
    while (*(tmp + offset) == ' ')
        offset++;
    strcpy(tmp, (tmp + offset));
  }
}
#define MAX(a,b) (((a)>(b))?(a):(b))

int 
strcmpnc(const char * str1, const char * str2){
  int i;
  int bo = 0;
  //int len = MAX(strlen(str1),strlen(str2));
  int len = strlen(str1);
  if(strcmp(str1,str2) == 0) 
    return bo;
  for(i = 0; i < len; i++){
    //printf(1, "input: %s %d\n",str1[i],(int) str1[i]);
    //printf(1, "compare to: %s %d\n",str2[i],(int) str2[i]);
    int a = (int) str1[i];
    int b = (int) str2[i];  
    
    if(a>=65 && a<=90) a = a + 32;
    if(b>=65 && b<=90) b = b + 32;
    if (a != b){
      bo = -1;
      break;
    }  
  }
  return bo;
}



int 
sortu(char *arr[], int n){
  int i;
  int c = 0;
  char temp1[512];
  sorts_selection(arr,n,0);
  //printf(1, "in sortu!\n");
  
  for (i = 0; i < n; i++) {
    if(strcmp(arr[i],arr[i+1]) == 0){
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);

      c = c+1;
    }
  }
  sorts_selection(arr,n-c,0);
  return c;
}

void
sortM(char *arr[], int n){

  //printf(1, "in sortM!\n");
  int i;
  int c = 0;
  char temp1[512];

  
  int j1 = 0;
  int j2 = 0;
  int j3 = 0;
  int j4 = 0;
  int j5 = 0;
  int j6 = 0;
  int j7 = 0;
  int j8 = 0;
  int j9 = 0;
  int j10 = 0;
  int j11 = 0;
  int j12 = 0;
  
  

  for (i = 0; i < n-c; i++){
    //printf(1,"n is %d\n",n);
    if(strcmpnc(arr[i], "dec") == 0||strcmpnc(arr[i], "december") == 0){
      //Dec[j12] = arr[i];
      //printf(1,"out %s\n",Dec[j12]);
      //printf(1,"num %d\n",j12);
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j12 = j12 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){

    if(strcmpnc(arr[i],"nov") == 0||strcmpnc(arr[i], "november") == 0){
      //Nov[j11] = arr[i];
      //printf(1,"%s",Nov[j11]);
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j11 = j11 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){

    if(strcmpnc(arr[i],"oct") == 0||strcmpnc(arr[i], "october") == 0){
      //Nov[j11] = arr[i];
      //printf(1,"%s",Nov[j11]);
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j10 = j10 + 1;
      c = c + 1;
    }
  }
 
  //printf(1,"c1 is %d\n",c);
  for (i = 0; i < n-c; i++){ 
    if(strcmpnc(arr[i], "Sep") == 0||strcmpnc(arr[i], "september") == 0||strcmpnc(arr[i], "sept") == 0){
      //Sep[j9] = arr[i];
      //printf(1,"%s",Sep[j9]);
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j9 = j9 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){
    if(strcmpnc(arr[i], "Aug") == 0||strcmpnc(arr[i], "august") == 0){
      //Aug[j8] = arr[i];
      
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j8 = j8 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){
    if(strcmpnc(arr[i], "jul") == 0||strcmpnc(arr[i], "july") == 0){
      //Jul[j7] = arr[i];
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j7 = j7 + 1;
      c = c + 1;
    }
  }
  
  //printf(1,"c1 is %d\n",c);
  for (i = 0; i < n-c; i++){
    if(strcmpnc(arr[i], "Jun") == 0||strcmpnc(arr[i], "june") == 0){//
      //Jun[j6] = arr[i];

      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j6 = j6 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c1 is %d\n",c);
  for (i = 0; i < n-c; i++){
    if(strcmpnc(arr[i], "may") == 0){
      //May[j5] = arr[i];

      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j5 = j5 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){
    if(strcmpnc(arr[i], "apr") == 0||strcmpnc(arr[i], "april") == 0){
      //Apr[j4] = arr[i];

      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j4 = j4 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){

    if(strcmpnc(arr[i], "mar") == 0||strcmpnc(arr[i], "march") == 0){
      //Mar[j3] = arr[i];

      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j3 = j3 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){

    if(strcmpnc(arr[i], "feb") == 0||strcmpnc(arr[i], "february") == 0){
      //Feb[j2] = arr[i];

      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j2 = j2 + 1;
      c = c + 1;
    }
  }
  //printf(1,"c is %d\n",c);
  for (i = 0; i < n-c; i++){

    if(strcmpnc(arr[i],"jan") == 0||strcmpnc(arr[i],"january") == 0){
      //Jan[j1] = arr[i];
      //printf(1,"out %s\n",Jan[j1]);
      //printf(1,"num %d\n",j1);
      strcpy(temp1,arr[i]);
      strcpy(arr[i],arr[n-c-1]);
      strcpy(arr[n-c-1],temp1);
      
      j1 = j1 + 1;
      c = c + 1;
    }
  }
 // printf(1,"c1 is %d\n",c);

  //printf(1,"n-c = %d\n",n-c);
 // printf(1,"sum is %d\n", j1+j2+j3+j4+j5+j6+j7+j8+j9+j10+j11+j12);
 
  sorts_selection(arr,n-c,0);
  sorts_selection(arr,n-c+j1,n-c);
  sorts_selection(arr,n-c+j1+j2,n-c+j1);
  sorts_selection(arr,n-c+j1+j2+j3,n-c+j1+j2);
  sorts_selection(arr,n-c+j1+j2+j3+j4,n-c+j1+j2+j3);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5,n-c+j1+j2+j3+j4);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6,n-c+j1+j2+j3+j4+j5);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7,n-c+j1+j2+j3+j4+j5+j6);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7+j8,n-c+j1+j2+j3+j4+j5+j6+j7);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9,n-c+j1+j2+j3+j4+j5+j6+j7+j8);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9+j10,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9+j10+j11,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9+j10);
  sorts_selection(arr,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9+j10+j11+j12,n-c+j1+j2+j3+j4+j5+j6+j7+j8+j9+j10+j11);
  

}



//selection sort
void 
sorts_selection(char *arr[], int n, int e){
  int i, j;
  int k;
  char temp2[512];

  for (i = e; i < n-1; i++){
    k = i;
    //strcpy(temp2, arr[k]);

    for (j = i+1; j < n; j++){
      if (comp(arr[k], arr[j]) > 0){
        //strcpy(temp2, arr[j]);
        k = j;
      }
    }

    if (k != i){
      strcpy(temp2, arr[i]);
      strcpy(arr[i], arr[k]);
      strcpy(arr[k], temp2);
    }
  }
}


void 
sort(int ifd, int ofd,int roption,int ooption,int noption, int boption, int Moption, int uoption){
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
        if(!Moption && !uoption){
            temp[j] = buf[i];
        }
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
    if(boption)
      sortb(txt,k);
    if(uoption)
       k = k - sortu(txt,k);
    if(Moption)
      sortM(txt,k);
    else
      sorts_selection(txt,k,0);
    for(i = k-1 ; i >= 0 ; i--){
      if(!Moption && !uoption){
        if(write(ofd, txt[i], strlen(txt[i])-1) != strlen(txt[i])-1|| write(ofd, "\n", 1) != 1) {
          printf(2, "sort: write error\n");
          exit();
        }
      }
      else{
        
        if(write(ofd, txt[i], strlen(txt[i])) != strlen(txt[i]) || write(ofd, "\n", 1) != 1) {
          printf(2, "sort: write error\n");
          exit();
        }

      }
    }
  }
  else{
    if(boption)
      sortb(txt,k);
    if(noption)
      sortn(txt,k);  
    if(uoption)
      k = k - sortu(txt,k);
    if(Moption)
      sortM(txt,k);
    else
      sorts_selection(txt,k,0);
    
    for(i = 0 ; i < k ; i++){
       if(!Moption && !uoption){
        if(write(ofd, txt[i], strlen(txt[i])-1) != strlen(txt[i])-1|| write(ofd, "\n", 1) != 1) {
          printf(2, "sort: write error\n");
          exit();
        }
      }
      else{

        if(write(ofd, txt[i], strlen(txt[i])) != strlen(txt[i]) || write(ofd, "\n", 1) != 1) {
          printf(2, "sort: write error\n");
          exit();
        }
        
      }
    } 
  }
}

int
main(int argc, char *argv[]){
  int fo;
  int fs = 0;
  int r = 0, o = 0, n = 0, b = 0, M = 0, u = 0;

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
    sort(fo,fs,r,o,n,b,M,u);
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
        case 'b':
          b = 1;
          break;
        case 'M':
          M = 1;
          break;
        case 'u':
          u = 1;
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
      sort(fo,fs,r,o,n,b,M,u);
      close(fo);
      close(fs);
    }  
    /*not -o*/
    else{
      if((fo = open(argv[2], 0)) < 0){
      printf(1, "sort: cannot open %s\n", argv[2]);
      exit();
    }
    sort(fo,0,r,o,n,b,M,u);
    close(fo);  
    }
  }
  ut = uptime();
  printf(1, "up %d ticks\n", ut);
  exit();
}
