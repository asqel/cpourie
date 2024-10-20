CC = gcc
LD = gcc

CFLAGS = -Iinclude
LDFLAGS =

DEBUG_FLAG = -g

SRC = main.c $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c)
BIN = $(SRC:.c=.o)

OUT_DIR = build
OUT_NAME = cpourie

ifeq ($(OS),Windows_NT)
		OUT = $(OUT_DIR)/$(OUT_NAME).exe
else
	OUT = $(OUT_DIR)/$(OUT_NAME)
endif



all: $(OUT) run

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

add_debug_flags:
	CFLAGS += $(DEBUG_FLAG)

debug: add_debug_flags build
	valgrind $(OUT)

clean:
ifeq ($(OS),Windows_NT)
	powershell -NoProfile -Command rm -r -force $(BIN)
else
	rm -rf $(BIN)
endif

fclean: clean
ifeq ($(OS),Windows_NT)
	powershell -NoProfile -Command rm -r -force $(OUT)
else
	rm -rf $(OUT)
endif