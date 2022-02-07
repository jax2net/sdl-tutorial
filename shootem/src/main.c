#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "structs.h"
#include "draw.h"
#include "constants.h"

static App app;
static Entity player;

void init(void);
void shutdown(void);

int main(int argc, char** argv) {

    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    init();
    
    SDL_Event e;
    int exit = 0;

    SDL_Texture* mike = load_texture_from_file("../assets/mike.jpg", app.renderer);

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }

        SDL_SetRenderDrawColor(app.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(app.renderer);

        //render here
        blit(mike, 50, 50, app.renderer);

        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }

    shutdown();

    SDL_Quit();
    return 0;
}


void init(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialize image subsystem: %s\n", IMG_GetError());
    }

    if (TTF_Init() < 0) {
        printf("Failed to initialize TTF subsystem: %s\n", TTF_GetError());
    }
    
    app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (app.window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
    }
}

void shutdown(void) {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);

    TTF_Quit();
    IMG_Quit();
    
}
