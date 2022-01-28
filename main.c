#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* load_surface(char* path) {
    SDL_Surface* loaded_surface = SDL_LoadBMP(path);
    return loaded_surface;
}


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Surface *current_surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL!: %s\n", SDL_GetError());
        exit(0);
    }

    window = SDL_CreateWindow("SDL hi world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    screen = SDL_GetWindowSurface(window);

    int quit = 0;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                    current_surface = load_surface("up.bmp");
                    break;
                case SDLK_DOWN:
                    current_surface = load_surface("down.bmp");
                    break;
                case SDLK_LEFT:
                    current_surface = load_surface("left.bmp");
                    break;
                case SDLK_RIGHT:
                    current_surface = load_surface("right.bmp");
                    break;
                }
            }
        }
        SDL_BlitSurface(current_surface, NULL, screen, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}
