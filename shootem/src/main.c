#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "constants.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf("Failed to initialize image subsystem: %s\n", IMG_GetError());
    }

    if (TTF_Init() < 0) {
        printf("Failed to initialize TTF subsystem: %s\n", TTF_GetError());
    }
    
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
    }
    
    SDL_Event e;
    int exit = 0;

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        //render here

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    
    SDL_Quit();
    return 0;
}
