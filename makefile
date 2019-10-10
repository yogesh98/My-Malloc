all: mymalloc.c mymalloc.o
				gcc mymalloc.c mymalloc.object
		mymalloc.o: mymalloc.c
				gcc -c mymalloc.c
clean:
				rm a.out; rm library.o
