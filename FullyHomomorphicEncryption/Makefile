CC=gcc
CFLAGS=-Wall

FHEv1: FHEv1.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
	$(CC) $(CFLAGS) -o FHEv1 FHEv1.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
clean:
	rm FHEv1
	rm *.o
	rm keyFile
