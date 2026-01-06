CC = gcc
FLAGS = -Wall -Wextra -g `pkg-config --cflags --libs sdl2 SDL2_image`
TARGET = gol.out
SRC = main.c gui.c gol_helpers.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lSDL2 -lSDL2_image -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.d *.out *.gol