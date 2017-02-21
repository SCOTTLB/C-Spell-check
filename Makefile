####																		####
# Scott Bean (40274024)										 #
# Programming Fundamentals Coursework 1		 #
#																					 #
####																		####


all: spell.c
	clear
	gcc -c spell.c -o spell.o
	gcc spell.o -o spell
	rm *.o
	./spell -c


clean:
	rm *.o
	rm spell
