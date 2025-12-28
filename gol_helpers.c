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