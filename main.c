// Andrzej Kalinowski 2025
// Implementation of the classic Conway's Game of Life
// using C and SDL2

// Basic C includes
#include <stdlib.h>
#include <stdio.h>

// SDL2 include
#include <SDL2/SDL.h>

// Some defines
#define GOL_WIDTH 80   // how many columns of cells
#define GOL_HEIGHT 80  // how many rows of cells

#define CELL_SIZE 10

#define SCREEN_WIDTH    GOL_WIDTH*CELL_SIZE     // in pixels
#define SCREEN_HEIGHT   GOL_HEIGHT*CELL_SIZE    // in pixels

// A function that counts how many alive neighbors does a cell at (x, y) have
int CountAliveNeighbors(int cell_array[GOL_WIDTH][GOL_HEIGHT], int x, int y){
    int count = 0;
    if(cell_array[x - 1][y - 1] == 1)
        count++;
    if(cell_array[x - 1][y] == 1)
        count++;
    if(cell_array[x - 1][y + 1] == 1)
        count++;
    if(cell_array[x][y - 1] == 1)
        count++;
    if(cell_array[x][y + 1] == 1)
        count++;
    if(cell_array[x + 1][y - 1] == 1)
        count++;
    if(cell_array[x + 1][y] == 1)
        count++;
    if(cell_array[x + 1][y + 1] == 1)
        count++;
    return count;
}

int main(int argc, char* argv[]){
    (void) argc;
    (void) argv;

    // Initializing SDL2
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cellular automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;

    // Initializing an array containing cell states
    int cell_states[GOL_WIDTH][GOL_HEIGHT];
    int cell_states_new[GOL_WIDTH][GOL_HEIGHT];
    // Filling the arrays with zeros (at the begining all cells are dead)
    for(int i = 0; i < GOL_WIDTH; i++){
        for(int j = 0; j < GOL_HEIGHT; j++){
            cell_states[i][j] = 0;
            cell_states_new[i][j] = 0;
        }   
    }
    // cell_states[50][50] = 1;    // for testing
    // A simple blinker is defined:
    cell_states[60][30] = 1;    // for testing
    cell_states[60][31] = 1;    // for testing
    cell_states[60][32] = 1;    // for testing

    int quit = 0;
    int pause = 0;
    while(!quit){
        while(SDL_PollEvent(&e)){
            switch (e.type){
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == 32){
                        // Pause if space is pressed
                        pause = !pause;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Changing the state of a cell if it is clicked
                    cell_states[(int) e.motion.x/CELL_SIZE][(int) e.motion.y/CELL_SIZE] = !cell_states[(int) e.motion.x/CELL_SIZE][(int) e.motion.y/CELL_SIZE];
                    break;
                default:
                    break;
            }
        }

        // Clearing the screen with a dark gray background
        SDL_SetRenderDrawColor(renderer, 0x00, 0x05, 0x05, 0xFF);
        SDL_RenderClear(renderer);
        
        // Drawing grid lines
        SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xff);   // grid lines color - gray
        for(int i = 0; i <= GOL_HEIGHT; i++){
            SDL_RenderDrawLine(renderer, 0, i*CELL_SIZE, SCREEN_WIDTH, i*CELL_SIZE);
        }
        for(int i = 0; i <= GOL_WIDTH; i++){
            SDL_RenderDrawLine(renderer, i*CELL_SIZE, 0, i*CELL_SIZE, SCREEN_HEIGHT);
        }

        // Drawing the cells, according to their state
        SDL_SetRenderDrawColor(renderer, 0x50, 0xa0, 0xee, 0xff);   // alive cell color - light blue
        SDL_Rect cell_square;
        cell_square.w = CELL_SIZE;
        cell_square.h = CELL_SIZE;
        for(int i = 0; i < GOL_WIDTH; i++){
            for(int j = 0; j < GOL_HEIGHT; j++){
                if(cell_states[i][j]){
                    cell_square.x = i*CELL_SIZE;
                    cell_square.y = j*CELL_SIZE;
                    SDL_RenderFillRect(renderer, &cell_square);
                }
            }
        }
        if(!pause){
            // Updating cell states according to the rules of gol
            for(int i = 0; i < GOL_WIDTH; i++){
                for(int j = 0; j < GOL_HEIGHT; j++){
                    if(CountAliveNeighbors(cell_states, i, j) == 3){
                        cell_states_new[i][j] = 1;
                    }
                    else if(cell_states[i][j] == 1 && CountAliveNeighbors(cell_states, i, j) == 2){
                        cell_states_new[i][j] = 1;
                    }
                    else{
                        cell_states_new[i][j] = 0;
                    }
                }
            }
            // Coping the contents of "new" array to the main one
            for(int i = 0; i < GOL_WIDTH; i++){
                for(int j = 0; j < GOL_HEIGHT; j++){
                    cell_states[i][j] = cell_states_new[i][j];
                }
            }
        }
        SDL_RenderPresent(renderer);    // Updating screen
        SDL_Delay(200);
    }

    // Quitting
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}