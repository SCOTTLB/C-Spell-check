#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  char word1[10];
  char word2[10];

  strcpy(word1, "all");
  strcpy(word2, "alpaca");

  int ret = strcmp(word1, word2);


  if(ret < 0 ){
    printf("%s is less than %s!\n",word1, word2);

  }else if(ret > 0){

    printf("%s is less than %s!\n",word2, word1);
  }else if(ret == 0){

    printf("Equal\n");
  }

  return 0;
}
