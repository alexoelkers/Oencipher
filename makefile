all: src/main.c libs/feistel.c
	$(MAKE) -C libs
	$(MAKE) -C src
	cp ./src/cipher ./test

clean:
	rm libs/*.o
	rm src/*.o src/cipher
	rm test/cipher

test: all
	cd src
	$/cipher test.txt a.key -e out.txt
	$/cipher out.txt a.key -d r.txt