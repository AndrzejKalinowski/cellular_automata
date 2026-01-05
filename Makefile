CC = gcc
FLAGS = -Wall -Wextra -g
TARGET = gol.out
SRC = main.c gui.c gol_helpers.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lSDL2 -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.d *.out *.gol