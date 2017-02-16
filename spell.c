    /////////////////////////////////
   // Scott Bean (40274024)       //
  // Programming Fundamentals    //
 // Coursework 1                //
/////////////////////////////////

// TODO: Remeber to close failes



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
  printf("\nSpell Check Tool - Scott Bean\nUsage:\n\tspell [options]\nExample:\n\tspell -i input_file.txt -o output_file.txt\n\nOptions\n-i <file>\t\tThe file to spell check\n-o <file>\t\tThe file to write misspelt words to\n-c\t\t\tIgnore case of words\n");

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

int main(int argc, char *argv[]) {

  // Flags
  int input_file, output_file, case_sensitive = 0;

  // Hold the filename
  char* fileName = "";

  // Handle arguments
  for(int i = 0; i < argc; i ++){

    // Input flag
    if(strcmp(argv[i], "-i") == 0 ){

      printf("Input arg\n");
      // Set flag
      input_file = 1;

      // Check filename (arg + 1) contains '.txt', if so set the filename otherwise display an error
      if(strstr(argv[i+1], ".txt") != NULL){

        fileName = argv[i+1];

      }else{

        printf("Invalid filename\n\n");
        CLIhelper();
        exit(1);

      }
    }

    if(strcmp(argv[i], "-o") == 0 ){

      printf("Out arg\n");
      output_file = 1;
    }

    if(strcmp(argv[i], "-h") == 0 ){

      printf("Help arg\n");
      CLIhelper();
    }

    if(strcmp(argv[i], "-c") == 0){

      printf("Case arg\n");
      case_sensitive = 1;
    }
  }

  if(fileName){
    int size  = lineNumber(fileName);

    char** dictionary = fileHandler(size, fileName);
    printf("File: %s: Lines: %d\n",fileName, size);

  }else{

    printf("No file, using standard in\n");

  }


  return 0;
}
