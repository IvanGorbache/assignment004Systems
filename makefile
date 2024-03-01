all: encodemain.o compress.o digitcompress

digitcompress: encodemain.o compress.o
	gcc -Wall encodemain.o compress.o -o digitcompress

encodemain.o: encodemain.c compress.h
	gcc -c -Wall encodemain.c

StrList.o: compress.c compress.h
	gcc -c -Wall compress.c

clean:
	rm -f *.o digitcompress
