// Andrzej Kalinowski 2025
// Implementation of the classic Conway's Game of Life
// using C and SDL2

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "gui.h"
#include "gol_helpers.h"

// Some defines
#define GOL_MAX_WIDTH 200   // maximum allowed number of columns of cells
#define GOL_MAX_HEIGHT 200  // maximum allowed number of columns of cells
#define CELL_SIZE 10
#define GUI_HEIGHT 100

int main(int argc, char* argv[]){

    // Handling arguments
    int w, h;
    if(argc == 3){
        w = atoi(argv[1]);
        h = atoi(argv[2]);
    }
    else{
        w = 70;
        h = 70;
    }
    const int gol_texture_width = w * CELL_SIZE;
    const int gol_texture_height = h * CELL_SIZE;
    const int screen_width = gol_texture_width;
    const int screen_height = gol_texture_height + GUI_HEIGHT;    // including space for the interface

    test_gui();

    // Initializing SDL2
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("cellular automata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* gol_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, gol_texture_width, gol_texture_height);
    SDL_Event e;
    // Gol texture copy destination
    SDL_Rect dst;
    dst.w = gol_texture_width;
    dst.h = gol_texture_height;
    dst.x = 0;
    dst.y = GUI_HEIGHT;

    // Dynamically initializing two arrays for storing cell states
    int** cell_states = malloc(w * sizeof(int *));
    int** cell_states_new = malloc(w * sizeof(int *));
    cell_states[0] = malloc(w * h * sizeof(int));
    cell_states_new[0] = malloc(w * h * sizeof(int));
    for(int i = 0; i < w; i++){
        cell_states[i] = cell_states[0] + i * h;
        cell_states_new[i] = cell_states_new[0] + i * h;
    }
    // Filling the arrays with zeros (at the begining all cells are dead)
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            cell_states[i][j] = 0;
            cell_states_new[i][j] = 0;
        }   
    }
    // A simple blinker is defined:
    // cell_states[60][30] = 1;    // for testing
    // cell_states[60][31] = 1;    // for testing
    // cell_states[60][32] = 1;    // for testing

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
                    cell_states[(int) e.motion.x/CELL_SIZE][(int) (e.motion.y - GUI_HEIGHT)/CELL_SIZE] = !cell_states[(int) e.motion.x/CELL_SIZE][(int) (e.motion.y - GUI_HEIGHT)/CELL_SIZE];   // offsetting by gui height
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderTarget(renderer, gol_texture);
        // Clearing the screen with a dark gray background
        SDL_SetRenderDrawColor(renderer, 0x00, 0x05, 0x05, 0xFF);
        SDL_RenderClear(renderer);
        
        // Drawing grid lines
        SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xff);   // grid lines color - gray
        for(int i = 0; i <= h; i++){
            SDL_RenderDrawLine(renderer, 0, i*CELL_SIZE, screen_width, i*CELL_SIZE);
        }
        for(int i = 0; i <= w; i++){
            SDL_RenderDrawLine(renderer, i*CELL_SIZE, 0, i*CELL_SIZE, screen_height);
        }

        // Drawing the cells, according to their state
        SDL_SetRenderDrawColor(renderer, 0x50, 0xa0, 0xee, 0xff);   // alive cell color - light blue
        SDL_Rect cell_square;
        cell_square.w = CELL_SIZE;
        cell_square.h = CELL_SIZE;
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                if(cell_states[i][j]){
                    cell_square.x = i*CELL_SIZE;
                    cell_square.y = j*CELL_SIZE;
                    SDL_RenderFillRect(renderer, &cell_square);
                }
            }
        }
        if(!pause){
            // Updating cell states according to the rules of gol
            for(int i = 0; i < w; i++){
                for(int j = 0; j < h; j++){
                    int count = CountAliveNeighbors(cell_states, w, h, i, j);
                    if(count == 3){
                        cell_states_new[i][j] = 1; 
                    }
                    else if(cell_states[i][j] == 1 && count == 2){
                        cell_states_new[i][j] = 1;
                    }
                    else{
                        cell_states_new[i][j] = 0;
                    }
                }
            }
            // Coping the contents of "new" array to the main one
            memcpy(cell_states[0], cell_states_new[0], w * h * sizeof(*cell_states_new[0]));  // maybe more efficient
        }
        
        // Updating screen
        SDL_RenderPresent(renderer);    
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, gol_texture, NULL, &dst);
        SDL_Delay(50 + 180*!pause); // slowing it down, speeding it up if paused (for less lag when clicking)
    }

    // Quitting
    free(cell_states[0]);
    free(cell_states);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}