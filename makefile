all: memgrind mymalloc
	memgrind: mymalloc.o
		gcc -o memgrind memgrind.c mymalloc.o
	mymalloc: mymalloc.c
		gcc -c mymalloc.c
clean:
	rm a.out; rm mymalloc.o
