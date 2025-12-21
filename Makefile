all: main

main: 
	gcc main.c -lSDL2 -o app.out

run: all
	./app.out