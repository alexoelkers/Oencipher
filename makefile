all: src/main.c
	$(MAKE) -C libs
	$(MAKE) -C src