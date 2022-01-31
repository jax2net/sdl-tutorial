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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
    SDL_Texture* ture;
    int w, h;
} LTexture;

TTF_Font *font = NULL;
LTexture font_texture;

void free_texture(LTexture* obj) {
    if (obj != NULL) {
        SDL_DestroyTexture(obj->ture);
        obj->ture = NULL;
        obj->w = 0;
        obj->h = 0;
    }
}

void load_font(char* texture_text, LTexture* obj) {
    SDL_Color text_color = { 0, 0, 0 };
    font = TTF_OpenFont("lazy.ttf", 28);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }
    
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, texture_text, text_color);
    if (text_surface == NULL) {
        printf("Can't create texture from rendered text: %s\n", SDL_GetError());
    }
    
    obj->ture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (obj->ture == NULL) {
        printf("ERROR IN creating texture from surface: %s\n", TTF_GetError());
    }
    
    obj->w = text_surface->w;
    obj->h = text_surface->h;
    SDL_FreeSurface(text_surface);
}

void render(int x, int y, LTexture* obj) {
    SDL_RenderCopy(renderer, obj->ture, NULL, NULL);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Cannot initialize video: %s\n", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Can't initialize image loading: %s\n", IMG_GetError());
    }

    if (TTF_Init() == -1) {
        printf("Can't initialize text: %s\n", TTF_GetError());
    }

    window = SDL_CreateWindow("TTF rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Can't create window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Can't create renderer: %s\n", SDL_GetError());
    }

    SDL_Event e;
    int exit = 0;

    // load text
    load_font("ANthoy Fantano", &font_texture);

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);


        // render here   
        render((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), &font_texture);
        
        SDL_RenderPresent(renderer);
        
    }

    // shutdown subsystems
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    

    SDL_Quit();
    return 0;
        
}
