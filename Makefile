CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = LogiCDetetive
SAVES_DIR = saves

all: $(SAVES_DIR) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SAVES_DIR):
	mkdir -p $(SAVES_DIR)

run: all
	./$(BIN)


clean:
	rm -f src/*.o $(BIN)


rebuild: clean all
