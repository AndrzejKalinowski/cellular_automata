#include <stdio.h>
#include "gol_helpers.h"

// A function that counts how many alive neighbors does a cell at (x, y) have
int CountAliveNeighbors(int** cell_array, int w, int h, int x, int y){
    int count = 0;
    int x_tmp, y_tmp;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            x_tmp = (x + i + w) % w;
            y_tmp = (y + j + h) % h;
            count += cell_array[x_tmp][y_tmp];
        }
    }
    count -= cell_array[x][y];
    return count;
}

// Filling a 2D array with zeros
void clearGol(int** arr, int w, int h){
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            arr[i][j] = 0;
            arr[i][j] = 0;
        }   
    }
}

// Open a file in a convenient way
FILE* openGolFile(char *filename){
    FILE* f;
    // Opening the file
    printf("Opening file %s \n", filename);
    f = fopen(filename, "r+");
    if(f == NULL){
        // Creating the file if does not exist
        printf("File created \n");
        f = fopen(filename, "w+");
    }
    if(f == NULL){
        // Something went wrong
        printf("File error \n");
        return NULL;
    }
    return f;
}

// Saving the game state to a file
void saveState(int** arr, int w, int h, FILE* f){
    rewind(f);
    fprintf(f, "%d %d \n", w, h);
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            fprintf(f, "%d ", arr[i][j]);
        }
        fprintf(f, "\n");
    }
}

// Loading the game state form a file
void loadState(int** arr, int w, int h, FILE* f){
    rewind(f);
    fscanf(f, "%*[^\n]\n");    // discarding the first liner
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            fscanf(f, "%d ", &arr[i][j]);
        }
    }
}