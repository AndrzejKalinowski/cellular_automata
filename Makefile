CC = gcc
FLAGS = -Wall -Wextra -g
TARGET = app.out
SRC = main.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(FLAGS) $(SRC) -lSDL2 -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)