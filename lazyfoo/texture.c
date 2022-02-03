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

SDL_Texture* load_texture(char* path, SDL_Renderer* renderer) {
    SDL_Texture* result = NULL;

    SDL_Surface* loaded_img = IMG_Load(path);

    result = SDL_CreateTextureFromSurface(renderer, loaded_img);
    SDL_FreeSurface(loaded_img);
    
    return result;
}


int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init video :%s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Texture stuff", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
    }

    

    // init renderer draw color
    
    texture = load_texture("dice.png", renderer);

    SDL_Event e;
    int exit = 0;

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) exit = 1;
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_Rect rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
