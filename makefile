CC = gcc
LD = gcc

CFLAGS = -Iinclude -Wall -Wextra
LDFLAGS =

DEBUG_FLAG = -g

SRC = main.c $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c)
BIN = $(SRC:.c=.o)

OUT_DIR = ./
OUT_NAME = cpourie

ifeq ($(OS),Windows_NT)
	OUT = $(OUT_DIR)/$(OUT_NAME).exe
	RM = powershell -NoProfile -Command rm -r -force
else
	OUT = $(OUT_DIR)/$(OUT_NAME)
	RM = rm -f
endif



all: $(OUT)

build: $(OUT)

$(OUT): $(BIN)
ifeq ($(OS),Windows_NT)
	if not exist $(OUT_DIR) mkdir $(OUT_DIR)
else
	mkdir -p $(OUT_DIR)
endif
	$(LD) $(LDFLAGS) $(BIN) -o $(OUT)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	./$(OUT)


debug:
	$(CC) $(DEBUG_FLAG) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)
	valgrind $(OUT)

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(OUT)

re: fclean all

.PHONY: all build run debug clean fclean re