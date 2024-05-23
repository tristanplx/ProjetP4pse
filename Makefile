CC = gcc
CFLAGS = -Wall -Wextra -lm

SRC_ORDINATEUR = ordinateur/ordinateur.c
SRC_JEU = jeu/jeu.c
SRCS = $(SRC_ORDINATEUR) $(SRC_JEU)
OBJS = $(SRC_ORDINATEUR:.c=.o) $(SRC_JEU:.c=.o)
EXECUTABLE = totexec

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

ordinateur/ordinateur.o: ordinateur/ordinateur.c ordinateur/ordinateur.h
	$(CC) $(CFLAGS) -c -o $@ $<

jeu/jeu.o: jeu/jeu.c jeu/jeu.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXECUTABLE)

