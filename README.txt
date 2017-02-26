################################################################################
################################################################################
##                                                                            ##
##                           Scott's Spellchecker                             ##
##                                  2017                                      ##
##                                                                            ##
################################################################################
################################################################################

Description:

  Spell is a spellchecking tool written in C that looks for errors in any
  give string of text. The text can either be within a txt file or provided
  using the console. The tool will then output errors to a file or print to
  the console. By default, the tool will search taking into account the case
  of the input words, this behaviour can be changed using the command line arguments.

--------------------------------------------------------------------------------

Build:

    Building through command line:

      llvm/clang/gcc can used to build the tool from the source code, i'll use gcc
      in this example.

      1. Open terminal in the correct directory
      2. Compile the source code into object code using - "gcc -c spell.c -o spell.o"
      3. Link the object code and output a executable - "gcc spell.o -o spell"
      4. Run the tool - "./spell [arguments]"

    Building with make:

      'make' - builds the spell tool with no arguments

      'make single' - builds the spell tool with the 'single_words_test.txt' input file and output to 'single.txt'

      'make singlecase' - builds the spell tool with the 'single_words_test.txt' input file, ignores case and output to 'singlecase.txt'

      'make sentence' - builds the spell tool with the 'sentence_test.txt' input file and output to 'sentence.txt'

      'make sentencecase' - builds the spell tool with the 'sentence_test.txt' input file, ignores case and output to 'sentencecase.txt'

    Toolchain versions:

      GNU make - 3.81
      LLVM/Clang - 8.0.0

--------------------------------------------------------------------------------

Use and arguments:

    Command structure:

      ./spell [args]

    Arguments:

      |    Name     |     Flag      |                  Description                   |
      |-------------|---------------|------------------------------------------------|
      | Help        | -h            | Displays the help page                         |
      | Input file  | -i <filename> | Allows a input text file to be used            |
      | Output file | -o <filename> | Specifies the file to output misspelt words to |
      | Ignore case | -c            | Ignores the case of the word                   |


      * if no input file is specified, spell will use stdin

      * if no output file is specified, spell will use stdout


    Example use:

      ./spell -i myDoc.txt -o mistakes.txt

      This will run the spell check on every word in the myDoc.txt file and output any errors to mistakes.txt

--------------------------------------------------------------------------------

Author: Scott Bean (40274024)
Date last modified: 26/02/17
Module: Programming Fundamentals
