# Makefile pour le mini gestionnaire de fichiers OS

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
EXEC = gestionnaire_fs
SRC = main.c projetOS.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c projetOS.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

mrproper: clean
	rm -f *.o *~