CC=gcc
CFLAGS=-c

all: library

library: projecto.o list_livro.o list_requisit.o list_utente.o fila.o auxiliares.o
	$(CC) projecto.o list_livro.o list_requisit.o list_utente.o fila.o auxiliares.o -o library

projecto.o: projecto.c
	$(CC) $(CFLAGS) projecto.c 

list_livro.o: list_livro.c
	$(CC) $(CFLAGS) list_livro.c 

list_requisit.o: list_requisit.c
	$(CC) $(CFLAGS) list_requisit.c

list_utente.o: list_utente.c
	$(CC) $(CFLAGS) list_utente.c

fila.o: fila.c
	$(CC) $(CFLAGS) fila.c

auxiliares.o: auxiliares.c
	$(CC) $(CFLAGS) auxiliares.c

clean:
	rm -rf *o
clean2:
	rm -rf library

