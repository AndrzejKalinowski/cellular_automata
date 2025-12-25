CC = gcc
FLAGS = -Wall -Wextra -g
TARGET = app.out
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lSDL2 -MD -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)