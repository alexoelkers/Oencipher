all: src/main.c
	$(MAKE) -C libs
	$(MAKE) -C src

clean: 
	$(MAKE) -C libs
	$(MAKE) -C src