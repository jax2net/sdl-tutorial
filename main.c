#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* load_bmp(char* path) {
    SDL_Surface* loaded_surface = SDL_LoadBMP(path);
    return loaded_surface;
}

SDL_Surface* load_png(char* path) {
    SDL_Surface* loaded_surface = IMG_Load(path);
    return loaded_surface;
}

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Surface *optimized = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL!: %s\n", SDL_GetError());
        exit(0);
    }

    // initialize png loading
    int img_flags = IMG_INIT_PNG;
    if (img_flags < 0) {
        printf("Could not init img for png: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("SDL hi world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    screen = SDL_GetWindowSurface(window);

    int quit = 0;
    SDL_Event e;

    // image
    SDL_Surface *img_surface = load_png("dice.png");
    optimized = SDL_ConvertSurface(img_surface, screen->format, 0);
    if (optimized == NULL) {
        printf("Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(img_surface);
    
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_BlitSurface(optimized, NULL, screen, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    
    SDL_Quit();
    return 0;
}
