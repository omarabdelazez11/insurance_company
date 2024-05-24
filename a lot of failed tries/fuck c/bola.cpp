#include <stdio.h>
#include <string.h>
typedef struct{
    int o;
    int b;
    char os[50];
}stu;
int main (){
    stu oomar;
    oomar.o =5;
        oomar.b =6;
  

   FILE* fptr;
   fptr = fopen("omar.csv","a");
fprintf(fptr,"omar");
fprintf(fptr,"omar,%d,%d,%s",oomar.o,oomar.b,oomar.os);
fclose(fptr);
FILE* omar;
char om[100];
omar = fopen("omar.csv","r");
while(fgets(om,100,omar)){
    printf("%s",om);
}

    
fclose(omar);

    return 0;
}