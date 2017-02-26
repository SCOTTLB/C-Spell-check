####																		####
# Scott Bean (40274024)										 #
# Programming Fundamentals Coursework 1		 #
#																					 #
####																		####


all: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	./spell -i sentences_test.txt


clean:
	rm *.o
	rm spell
