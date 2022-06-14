SOURCES = main.c btree.c
HEADERS = btree.h

all: main

main : 
	gcc -g -o $@ $(SOURCES)
 
.PHONY: clean, test

test: 
	./main

clean:
	rm ./main

