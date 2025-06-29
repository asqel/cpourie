CC = gcc
LD = gcc

CFLAGS = -Iinclude -Wall -Wextra -g
LDFLAGS =

SRC = main.c $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c)
BIN = $(SRC:.c=.o)


NAME = cpourie

ifeq ($(OS),Windows_NT)
	RM = powershell -NoProfile -Command rm -r -force
else
	RM = rm -f
endif


all: $(NAME)

build: $(NAME)

$(NAME): $(BIN)
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o $(NAME) $(BIN)


%.o: %.c
	@echo "Compiling $<"
	@$(CC) -c $< -o $@ $(CFLAGS)

debug: $(NAME)
	valgrind $(NAME)

clean:
	@echo "Removing .o files"
	@$(RM) $(BIN)

fclean: clean
	@echo "Removing $(NAME)"
	@$(RM) $(OUT)

re: fclean all

.PHONY: all build debug clean fclean re