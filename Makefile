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
	./spell -i single_words_test.txt
	

clean:
	rm *.o
	rm spell
