#include <stdio.h>
#include "gui.h"

// Draws a button, according to the hovered state
void draw_button(Button* button){
    SDL_SetRenderTarget(button->renderer, NULL);
    if(button->hovered){
        SDL_RenderCopy(button->renderer, button->b_hover_texture, NULL, &(button->b_rect));
    }
    else{
        SDL_RenderCopy(button->renderer, button->b_texture, NULL, &(button->b_rect));
    }
}

// Handles button presses and hovers, returns 1 if the button was pressed
int handle_button_event(Button* button, SDL_Event* e){
    SDL_Rect mouse_rect = {
        .w = 2,
        .h = 2,
        .x = e->motion.x,
        .y = e->motion.y,
    };
    button->hovered = SDL_HasIntersection(&(button->b_rect), &mouse_rect);
    return button->hovered && e->type == SDL_MOUSEBUTTONDOWN;
}