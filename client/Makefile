include ../Makefile.inc

EXE = client
SRC = client.c ../game/jeu.c ../ordinateur/ordinateur.c
OBJS = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ $(EXE)
