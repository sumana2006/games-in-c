CC = gcc
CFLAGS = -Wall -Iinclude

SRC = \
src/core/*.c \
src/games/*.c \
src/platform/*.c \
src/utils/*.c

OUT = games

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
