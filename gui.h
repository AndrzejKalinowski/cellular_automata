#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

// A struct that holds all the info about a button
typedef struct {
    SDL_Rect b_rect;
    SDL_Texture* b_texture;
    SDL_Texture* b_hover_texture;
    SDL_Renderer* renderer;
    int state;
    int hovered;
} Button;

// Handles button presses and hovers, returns 1 if the button was pressed
int handle_button_event(Button*, SDL_Event*);

// Draws a button, according to the hovered state
void draw_button(Button*);

#endif