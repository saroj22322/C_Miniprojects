#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *enterpass(char *pass) {
    int c, count = 0;
  system("/bin/stty raw");
  while((c=getchar()) != 13){
    if(c == 127) {
        printf("\b\b\b   \b\b\b");
        count--;
        continue;
    }
    printf("\b \b");
    putchar('*');
    pass[count] = c;
    count++;   
  }
  printf("\b\b  \b\b");
  pass[count] = '\0';
  system("/bin/stty cooked");
  return pass;
}

int main(void){
    char pass[100];
    char pass1[100];
    int confirm;
    do {
        printf("Enter your password : \n");
      enterpass(pass);
      printf("\nConfirm your password:\n");
      enterpass(pass1);
      if(strcmp(pass1,pass) == 0) {
        printf("\nPassword matched! Password entered : \"%s\"\n\n", pass);
        confirm = 0;
      }else {
        printf("\nNot matched ! \"%s\" and \"%s\". Please enter again!\n\n", pass, pass1);
        confirm = 1;
        }
    } while(confirm == 1);
  return 0;
}

