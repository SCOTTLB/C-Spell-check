####																		####
# Scott Bean (40274024)										 #
# Programming Fundamentals Coursework 1		 #
#																					 #
####																		####


all: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell

build: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	rm *.o

single: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell -i single_words_test.txt -o single.txt

singlecase: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell -i single_words_test.txt -o singlecase.txt -c

sentence: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell -i sentences_test.txt -o sentence.txt

sentencecase: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell -i sentences_test.txt -o sentencecase.txt -c

clean:
	rm *.o
	rm spell
