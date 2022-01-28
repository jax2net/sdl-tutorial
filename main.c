#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init(void);
int load_media(void);
void close(void);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

int init(void) {
    int success = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not init: %s\n", SDL_GetError());
        success = 0;
    } else {
        // create win
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
            success = 0;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

int load_media(void) {
    int success = 1;
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        success = 0;
    }
    return success;
}

void close(void) {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}



int main(int argc, char* argv[]) {
    if (!init()) {
        printf("Failed to init!\n");
    } else {
        if (!load_media()) {
            printf("Failed to load media!\n");
        } else {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(3000);
        }
    }
    close();
    return 0;
}
