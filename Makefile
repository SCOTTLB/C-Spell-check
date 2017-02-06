####																		####
# Scott Bean (40274024)										 #
# Programming Fundamentals Coursework 1		 #
#																					 #
####																		####


all: main.c
	gcc -c main.c -o main.o
	gcc main.o -o out
	./out
	rm *.o
