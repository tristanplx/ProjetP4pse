include ../Makefile.inc

EXE = serveur
SRC_ORDINATEUR = ../ordinateur/ordinateur.c
SRC_JEU = ../game/jeu.c
SRC_SERVEUR = serveur.c
OBJS = $(SRC_ORDINATEUR:.c=.o) $(SRC_JEU:.c=.o) $(SRC_SERVEUR:.c=.o)

all: ${EXE}

${EXE}: ${OBJS}
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ ${EXE}
