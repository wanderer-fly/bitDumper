CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: 4bit

4bit: 4bit.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -f 4bit
