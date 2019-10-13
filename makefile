all: memgrind
memgrind: mymalloc.o memgrind.c
		gcc memgrind.c mymalloc.o -o memgrind
mymalloc: mymalloc.c mymalloc.h
		gcc -c mymalloc.c
clean:
	rm a.out; rm mymalloc.o; memgrind
