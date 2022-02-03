// mouse.c
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
const char* WINDOW_TITLE = "mouse.c";

// globals
SDL_Window* window;
SDL_Renderer* renderer;

void init();
void shutdown();

enum ButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

typedef struct {
} ButtonSprite;

typedef struct {
    SDL_Point position;
    ButtonSprite current_sprite;
} Button;

int main() {
    init();

    SDL_Event e;
    int exit = 0;
    
    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
            if (e.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                printf("x: %i, y: %i\n", x, y);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                printf("SHOT! x: %i, y: %i\n", x, y);
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // render here
        // render();

        SDL_RenderPresent(renderer);
    }

    shutdown();
    SDL_Quit();
    return 0;
}
           
void init() {
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
}

void shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
}
