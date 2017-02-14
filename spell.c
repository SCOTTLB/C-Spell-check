    /////////////////////////////////
   // Scott Bean (40274024)       //
  // Programming Fundamentals    //
 // Coursework 1                //
/////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int lineNumber(char* fileName){

  // Open the file with the given filename
  FILE *fp = fopen(fileName, "r");

  // If the file failes to open then error and return
  if(fp == NULL){
    printf("No file!\n");
    return 0;
  }

  // Characters and lines
  int ch, lines = 0;

  // While its not the end of the file
  while(!feof(fp)){
    // get the char
    ch = fgetc(fp);
    // if the char is a new line char
    if(ch == '\n'){
      // add one to the line counter
      lines++;
    }
  }
  fclose(fp);
  // return the size of the file
  return lines;
}

void CLIhelper(){
  // This func shows the help page
  printf("\nSpell Check Tool - Scott Bean\nUsage:\n\tspell [options]\n\nOptions\n-i <file>\t\tThe file to spell check\n-o <file>\t\tThe file to write misspelt words to\n-c\t\t\tIgnore case of words\n");

}

int argumentHandler(int argc, char const *argv[]){


  // If only one argument is passsed then fail and display help
  if(argc < 2){
    printf("Not enough arguments\n");
    CLIhelper();
    return 1;
  }

  // Loop through argv
  for(int i = 0; i < argc; i++){


    printf("\nArg: %s\n", argv[i]);
    // Help flag
    if(strcmp(argv[i], "-h") == 0){
      printf("Help arg found!\n");
      //CLIhelper();
    }

    // Input Flag
    if(strcmp(argv[i], "-i") == 0){

      printf("Input arg found!\n");
      IN_FLAG = 1;
    }

    // Output flag
    if(strcmp(argv[i], "-o") == 0){

      printf("Output arg found!\n");
      OUT_FLAG = 1;
    }

    // Case flag
    if(strcmp(argv[i], "-c") == 0){

      printf("Case arg found!\n");
    }
    //printf("%s\n", argv[i]);

  }

  return IN_FLAG;
}

char** fileHandler(int size, char* filename){

  FILE *fp = fopen(filename, "r");

  char** dictionary = (char**)malloc(size * sizeof(char*));

  for(int i = 0; i < size; i++){

    char wordBuff[50];

    dictionary[i] = (char*)malloc(sizeof(char));

    fgets(wordBuff, 50, fp);

    strcpy(dictionary[i], wordBuff);

  }

  return dictionary;
}


int main(int argc, char const *argv[]) {

  char fileName[] = "dictionary.txt";

  int size  = lineNumber(fileName);

  char** dictionary = fileHandler(size, fileName);

  printf("Lines: %d\n", size);

  return 0;

}
