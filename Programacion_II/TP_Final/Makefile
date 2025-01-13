CC=gcc
CFLAGS= -O2 -Wall
main: main.c generacion.o utils.o
	$(CC) $(CFLAGS) -o main main.c generacion.o utils.o
generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c 

.PHONY: clean
clean:
	rm -rf *.o
