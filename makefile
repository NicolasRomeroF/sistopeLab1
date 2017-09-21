CC=gcc
CFLAGS=-I.

all: coordinador comparador

coordinador: coordinador.o
	$(CC) -o coordinador coordinador.o -I.
	rm coordinador.o

comparador: comparador.o
	$(CC) -o comparador comparador.o -I.
	rm comparador.o