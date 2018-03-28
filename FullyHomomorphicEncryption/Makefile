CC=gcc
CFLAGS=-Wall
all: FHEv1 FHEv2
FHEv1: FHEv1.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
	$(CC) $(CFLAGS) -o FHEv1 FHEv1.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
FHEv2: FHEv2.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
	$(CC) $(CFLAGS) -o FHEv2 FHEv2.o bigd.o bigdigits.o fullyHomomorphic.o bigdRand.o bigdigitsRand.o
clean:
	rm FHEv1
	rm FHEv2
	rm *.o
	rm keyFile
