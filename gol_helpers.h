#ifndef GOL_HELPERS
#define GOL_HELPERS

// A function that counts how many alive neighbors does a cell at (x, y) have
int CountAliveNeighbors(int**, int , int, int, int);

// Sets the whole 2D array to zeros
void clearGol(int**, int, int);

// Open a file in a convenient way
FILE* openGolFile(char* filename);

// Saving the game state to a file
void saveState(int**, int, int, FILE*);

// Loading the game state form a file
void loadState(int**, int, int, FILE*);

#endif