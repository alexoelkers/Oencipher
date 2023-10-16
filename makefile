all: src/main.c
	$(MAKE) -C libs
	$(MAKE) -C src

clean:
	rm libs/*.o
	rm src/*.o src/cipher
	rm src/out.txt src/r.txt

test: all
	cd src
	$/cipher test.txt a.key -e out.txt
	$/cipher out.txt a.key -d r.txt