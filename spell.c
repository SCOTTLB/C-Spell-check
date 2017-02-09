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

  // Get the size of the file
  int size;

  // Read the file to determine the size
  fread(&size, sizeof(char), 1, file);

  // Allocate the appropriate amount of mem
  *data = (char*)malloc(sizeof(char) * size);

  // Read the strings from the file; long*2 is needed to read the whole file,
  // long long just didnt cut it...
  fread(*data, sizeof(long)*2, size, file);

  // return the size of the list
 return size;
}


int main(int argc, char const *argv[]) {

  // TODO: Arg handling
  // TODO: The rest

  char *data;

  char filename[] = "dictionary.txt";

  int size = readFile(&data, filename);

  printf("%d\n", size);

  printf("%s\n", data);

  return 0;
}
