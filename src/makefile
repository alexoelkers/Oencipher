all: cipher

cipher: main.o
	gcc -o cipher main.o ../libs/feistel.o ../libs/feistel.h

main.o:
	gcc -c main.c

clean:
	rm -rf *.o
	rm cipher