    /////////////////////////////////
   // Scott Bean (40274024)       //
  // Programming Fundamentals    //
 // Coursework 1                //
/////////////////////////////////

#define DICTIONARY_FILE_NAME "dictionary.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function to count the number of lines in a file
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
// Displays the command line helper
void CLIhelper(){
  // This func shows the help page
  printf("\nSpell Check Tool - Scott Bean\nUsage:\n\tspell [options]\nExample:\n\tspell -i input_file.txt -o output_file.txt\n\nOptions:\n\t-i <file>\t\tThe file to spell check\n\t-o <file>\t\tThe file to write misspelt words to\n\t-c\t\t\tIgnore case of words\n\n");

}
// Handles all files coming into the app
char** fileHandlerIn(char* filename, int* inputSize){

  // open file in read mode
  FILE *fp = fopen(filename, "r");

  // first level of validation
  if(fp != NULL){

    // Check filename (arg + 1) contains '.txt', if so set the filename otherwise display an error
    if(strstr(filename, ".txt") != NULL){

      // Buffer to grab line
      char checkLn[100];

      int checkLn_flag = 1;

      // grab a line of the file
      fgets(checkLn, 100, fp);

      // rewind to the beginning of the file
      rewind(fp);

      // if that line contains spaces then sentence handle otherwise handle new line separated vals
      if(strstr(checkLn, " ")){

        // SENTENCES
        int pos, counter = 0;

        char buffer[1000];

        char* token;

        // allocate memory
        char** dictionary = (char**)malloc(sizeof(char*));

        // while its not the end of the file and fgets is not returning null
        while(!feof(fp) && fgets(buffer, 1000, fp) != NULL){


          int len = strlen(buffer);

          // loop form 0 to the length of the buffer
          for(int j = 0; j < len; j++){

            // check if its not a letter
            if(!isalpha(buffer[j])){
              // check if its redundant punctuation
              if(buffer[j] == ',' || buffer[j] == ' ' || buffer[j] == '\n'){
                // replace punctuation with a space
                buffer[j] = ' ';
              }
            }
          }

          int nextCap = 0;

          // for every word in buffer, splitting at the space
          for(token = strtok(buffer, " "); token != NULL; token = strtok(NULL, " ")){

            // shoult this be capatalised?
            if(nextCap){
              // capatalise the first letter
              token[0] = toupper(token[0]);
              // lower the flag
              nextCap = 0;

            }
            // is there a full stop or q mark in this word?
            if(strstr(token, ".") || strstr(token, "?")){
              // raise the flag, the next word should be capatalised
              nextCap = 1;
              // replace the full stop with a null terminator
              token[strlen(token) - 1] = '\0';
              while(strstr(token, ".")){
                token[strlen(token) - 1] = '\0';
              }
            }

            // allocate enough memeory for the string
            char* temp = (char*)malloc(sizeof(char) * strlen(token));
            char** tempDic = (char**)realloc(dictionary, sizeof(char*) * counter + 1);
            dictionary = tempDic;
            // memory error checking
            if(temp == NULL){

              printf("Error allocating memory");
              free(temp);
              exit(1);
            }else{

              dictionary[counter] = temp;
              strcpy(dictionary[counter], token);
              counter++;
            }

          }

        }

        fclose(fp);
        *inputSize = counter - 1;
        return dictionary;
        // End of spaces IF
        }else{

          // if words are on new lines

          int size = lineNumber(filename);

          // allows an additional value to be returned through a pointer
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

          fclose(fp);
          return dictionary;
        }// end of space check

      }else{

        printf("Invalid text file: %s\n", filename);
        CLIhelper();
        exit(1);
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
// Handles standard input
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
// Handles output
void output(char* filename, char* word){

  printf("1: %s\n", filename);
  if(strcmp(filename, "stdout") == 0){
    printf("2\n");
    fprintf(stdout, "Can't find: %s\n", word);

  }else{
    printf("3\n");
    FILE *fp = fopen(filename, "a");
    printf("4\n");
    if(fp == NULL){

      printf("5\n");
      printf("Cant open file\n");
    }else{

      printf("6\n");
      fprintf(fp, "%s\n", word);
      fclose(fp);
    }
  }
}
// Recursive binary search function
int binarySearch(char** values, int low, int middle, int high, char* value, int case_flag){

  /*
  values = array of values to search from
  n = length of values
  value =  the value to search for
  */

  // set bounds
  int min = low;
  int max = high;
  int mid = middle;
  // check if the case flag is raised
  if(case_flag){

    // loop through the word, convert each char to lower case
    // Value to lower loop
    for(int i = 0; i < strlen(value); i++){

      value[i] = tolower(value[i]);

    }
  }
  // set up the comparison
  int comp = strcmp(value, values[mid]);

  if(comp == 0){
    //printf("FOUND!\n");
    return 0;

  }else if(comp < 0){

    // set new bounds
    max = mid;
    mid = (min + max) / 2;

    if(case_flag){
      // if we have split the list untill the end
      if(min > mid){

        //printf("\nLOWER: %d:%d:%d\n",min, mid, max );
        return 1;

      }else{
        // continue search
        int ret = binarySearch(values, min, mid,max, value, case_flag);
        return ret;
      }

    }else{
      // if we have split the list untill the end
      if(min >= mid){

        //printf("\nLOWER: %d:%d:%d\n",min, mid, max );
        return 1;

      }else{
        // continue search
        int ret = binarySearch(values, min, mid,max, value, case_flag);
        return ret;
      }
    }
  }else if/* if the key is in the higher half of the list*/(comp > 0){

    // set new bounds
    min = mid;
    mid = (min + max) / 2;

    // if we have split the list untill the end
    if(min >= mid){
      //printf("\nHIGHER: %d:%d:%d\n",min, mid, max );
      return 1;

    }else{
      // continue search
      int ret = binarySearch(values, min, mid, max, value, case_flag);
      return ret;
    }

  }
  return 1;
}
// A function to cast pointer types, allows use of qsort
int cmpstr(const void* a, const void* b){

  const char** castCharA = (const char**)a;
  const char** castCharB = (const char**)b;
  return strcmp(*castCharA, *castCharB);
}
// Users binary search to compair words in the dictionary with a key
void spellcheck(char** dictionary, char** inputDic, int inputSize, int case_flag, int out_flag, char* output_file){

  // Get the size of the dictionary
  int dictionarySize = lineNumber(DICTIONARY_FILE_NAME);


  // If the case sensitivity flag has been raised
  if(case_flag){
    printf("\n\n################################\n# This search will ignore case #\n################################\n\n");

    // Loop through each word
    for(int i = 0; i < dictionarySize; i++){
      // Loop though each char of the word
      for(int j = 0; j < strlen(dictionary[i]); j++){
        // convert the char to lower case
        dictionary[i][j] = tolower(dictionary[i][j]);
      }
    }
    // sort the newly altered dictionary
    qsort(dictionary, dictionarySize, sizeof(char*), cmpstr);
  }else{

    printf("\n\n####################################\n# This search will not ignore case #\n####################################\n\n");
  }

  // loop through each input word
  for(int i = 0; i < inputSize; i++){

    // if the search doent find the orgininal value
    if(binarySearch(dictionary, 0, dictionarySize/2, dictionarySize, inputDic[i], case_flag)){

      // if there is more than one letter in the word

      if(strlen(inputDic[i]) > 1){

        if(islower(inputDic[i][1])){

          inputDic[i][0] = tolower(inputDic[i][0]);


          if(binarySearch(dictionary, 0, dictionarySize/2, dictionarySize, inputDic[i], case_flag)){

            output(output_file, inputDic[i]);

          }

        }
      }
    }
  }
}

// MAIN //
int main(int argc, char *argv[]) {

  // case sensitivity flag
  int case_flag, out_flag = 0;

  // Hold the filename
  char* input_file = "";
  char* output_file = "";

  // initalise var
  char** inputDic = NULL;
  // inputSize is a int pointer that gets set to the numer of lines in the inputDic array
  int inputSize;

  // load the dictionary data
  char** dictionary = fileHandlerIn(DICTIONARY_FILE_NAME, &inputSize);

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

        out_flag = 1;
        output_file = argv[i + 1];

      }else{

        printf("Invalid output file\n");\
        CLIhelper();
        exit(1);

      }

    }

    if(strcmp(argv[i], "-h") == 0 ){

      CLIhelper();
      exit(0);
    }

    if(strcmp(argv[i], "-c") == 0){
      case_flag = 1;
    }
  }


  // if there is a input file
  if(strcmp(input_file, "")){
    // get the size
    int size  = lineNumber(input_file);


  }else{

    // GET FROM STD IN
    inputDic = standardIN(&inputSize);

  }

  if(strcmp(output_file, "") == 0){

    output_file = "stdout";
  }

  spellcheck(dictionary, inputDic, inputSize, case_flag, out_flag, output_file);

  return 0;
}
