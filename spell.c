    /////////////////////////////////
   // Scott Bean (40274024)       //
  // Programming Fundamentals    //
 // Coursework 1                //
/////////////////////////////////

#include <stdio.h>
#include <stdlib.h>


int readFile(char **data, const char *filename){

  // Create a pointer to a file
  FILE *file;

  // Read the file using the name provided
  file = fopen(filename, "r");

  int size;

  fread(&size, sizeof(char), 1, file);

  *data = (char*)malloc(sizeof(char) * size);

  fread(*data, sizeof(char), size, file);

  printf("%s\n", *data);

 return size;
}


int main(int argc, char const *argv[]) {

  // TODO: Arg handling
  // TODO: The rest

  char *data;

  char filename[] = "dictionary.txt";

  int size = readFile(&data, filename);



  return 0;
}
