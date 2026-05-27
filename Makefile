CC = gcc
CFLAGS = -Wall -Iinclude

SRC = src/*.c
OUT = games

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
