CC = gcc
CFLAGS = -Wall -Wextra -lm

SRC_ORDINATEUR = ../ordinateur/ordinateur.c
SRC_JEU = jeu.c
SRCS = $(SRC_ORDINATEUR) $(SRC_JEU)

OBJS = $(SRC_ORDINATEUR:.c=.o) $(SRC_JEU:.c=.o)
EXECUTABLE = gamexec

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

../ordinateur/ordinateur.o: ../ordinateur/ordinateur.c ../ordinateur/ordinateur.h
	$(CC) $(CFLAGS) -c -o $@ $<

jeu.o: jeu.c jeu.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXECUTABLE)
