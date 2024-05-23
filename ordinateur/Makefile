CC = gcc
CFLAGS = -Wall -Wextra -lm

SRCS = ordinateur.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = botexec

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXECUTABLE)
