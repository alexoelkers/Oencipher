all: cipher

cipher: main.o
	gcc -o cipher main.c ../libs/oencipher.o ../libs/oencipher.h

main.o:
	gcc -c main.c

clean:
	rm -rf *.o
	rm cipher