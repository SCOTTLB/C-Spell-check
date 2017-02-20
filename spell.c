    /////////////////////////////////
   // Scott Bean (40274024)       //
  // Programming Fundamentals    //
 // Coursework 1                //
/////////////////////////////////

#define DicFileName "dictionary.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


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
  // close the file
  fclose(fp);
  // return the size of the file
  return lines;
}

void CLIhelper(){
  // This func shows the help page
  printf("\nSpell Check Tool - Scott Bean\nUsage:\n\tspell [options]\nExample:\n\tspell -i input_file.txt -o output_file.txt\n\nOptions:\n\t-i <file>\t\tThe file to spell check\n\t-o <file>\t\tThe file to write misspelt words to\n\t-c\t\t\tIgnore case of words\n\n");

}

char** fileHandlerIn(char* filename, int* inputSize){

  // open file in read mode
  FILE *fp = fopen(filename, "r");

  // first level of validation
  if(fp != NULL){

    // Check filename (arg + 1) contains '.txt', if so set the filename otherwise display an error
    if(strstr(filename, ".txt") != NULL){

      /*
      TODO:
         this section only works with a word on each line,
         need some form of ifElse block to check if sentence or not
      */

      int size = lineNumber(filename);

      *inputSize = size;

      // allocate a block of memory using the number of lines * the size of a char*
      char** dictionary = (char**)malloc(size * sizeof(char*));

      // for each line in the file
      for(int i = 0; i < size; i++){

        // have a buffer to hold each word
        char wordBuff[50];

        // allocate a block of memory within each index of the char**
        dictionary[i] = (char*)malloc(sizeof(char));

        // get the word from the file and put it into buffer
        fgets(wordBuff, 50, fp);

        // get the sting lenth
        int len =  strlen(wordBuff);

        // if it ends witn a new line, remove it and add null terminator
        if(len > 0 && wordBuff[len - 1] == '\n'){

          wordBuff[len - 1] = '\0';

        }

        // copy from the buffer into the dictionary
        strcpy(dictionary[i], wordBuff);

      }
      // close the file
      fclose(fp);
      printf("File: %s loaded!\n", filename);
      return dictionary;

    }


  }else{ /* If input_file is invalid */

    printf("Invalid filename\n\n");
    // Help page
    CLIhelper();
    // exit the prog
    exit(1);
  }

  return NULL;
}

char** standardIN(int* inputSize){

  // buffer to hold the lines
  char str[1000];

  printf("USING CONSOLE INPUT> ");

  // get the line from stdin
  fgets(str, 1000, stdin);

  // declare vars to hold everything
  const char delimiter[2] = " ";
  char* token;

  int counter = 0;

  // allocate memory
  char** inputContent = (char**)malloc(sizeof(char*) * strlen(str));

  // loop through each token untill we reach the end
  for(token = strtok(str, delimiter); token != NULL; token = strtok(NULL, delimiter)){

    // allocate mem for the token
    inputContent[counter] = malloc(strlen(token) + 1);

    // get the sting lenth
    int len =  strlen(token);

    // if it ends witn a new line, remove it and add null terminator
    if(len > 0 && token[len - 1] == '\n'){

      token[len - 1] = '\0';

    }

    // copy from token to the content array
    strcpy(inputContent[counter], token);

    counter++;

    char** temp = (char**)realloc(inputContent, sizeof(inputContent) * sizeof(char*));

    // check for successfull mem allocation
    if(temp != NULL){
      // if no error set pointer to temp
        inputContent = temp;

    }else{
      // free temp
      free(temp);

      // error and quit
      printf("Error allocating memory\n");
      exit(1);

    }
  }
  *inputSize = counter;
  return inputContent;

}

void binarySearch(char** values, int low, int middle, int high, char* value, int case_flag){

  /*
    values = array of values to search from
    n = length of values
    value =  the value to search for
  */

    // set bounds
    int min = low;
    int max = high;
    int mid = middle;

    int comp = strcmp(value, values[mid]);
    
    // if the key is in the lower half of the array
    if(comp < 0){

      max = mid;
      mid = (min + max) / 2;

      if(min == mid || mid == max){

        printf("%s is not in the dictionary\n", value);
      }else{
        binarySearch(values, min, mid,max, value, case_flag);
      }


    }else if/* if the key is in the higher half of the list*/(comp > 0){

      min = mid;
      mid = (min + max) / 2;

      if(min == mid || mid == max){

        printf("%s is not in the dictionary\n", value);
      }else{
        binarySearch(values, min, mid,max, value, case_flag);
      }

    }else if /* if the keys match */(comp == 0){

      printf("FOUND %s!\n", value);

    }

}

void spellcheck(char** dictionary, char** inputDic, int inputSize, int case_flag){

  // Get the size of the dictionary
  int dictionarySize = lineNumber(DicFileName);

  if(case_flag){
    printf("\n\n##############################\n# This file will ignore case #\n##############################\n\n");
  }

  for(int i = 0; i < inputSize; i++){

    binarySearch(dictionary, 0, dictionarySize/2, dictionarySize, inputDic[i], case_flag);
  }
}

// MAIN //

int main(int argc, char *argv[]) {

  // case sensitivity flag
  int case_flag = 0;

  // Hold the filename
  char* input_file = "";
  char* output_file = "";

  // initalise var
  char** inputDic = NULL;
  // inputSize is a int pointer that gets set to the numer of lines in the inputDic array
  int inputSize;


  // load the dictionary data
  char** dictionary = fileHandlerIn(DicFileName, &inputSize);

  // Handle arguments
  for(int i = 0; i < argc; i ++){

    // Input flag
    if(strcmp(argv[i], "-i") == 0 ){

      // Get the filename
      input_file = argv[i+1];
      // pass the file to fileHandlerIn
      inputDic = fileHandlerIn(input_file, &inputSize);

    }

    if(strcmp(argv[i], "-o") == 0 ){

      printf("Out arg\n");

      if (strstr(argv[i + 1], ".txt") != NULL){

        output_file = argv[i + 1];

      }else{

        printf("Invalid output file\n");\
        CLIhelper();
        exit(1);

      }

    }

    if(strcmp(argv[i], "-h") == 0 ){

      printf("Help arg\n");
      CLIhelper();
    }

    if(strcmp(argv[i], "-c") == 0){
      case_flag = 1;
    }
  }


  // if there is a input file
  if(strcmp(input_file, "")){
    // get the size
    int size  = lineNumber(input_file);

    printf("File: %s: Lines: %d\n",input_file, size);

  }else{

    // GET FROM STD IN
    inputDic = standardIN(&inputSize);

  }

  spellcheck(dictionary, inputDic, inputSize, case_flag);


  return 0;
}
