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

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct {
    SDL_Texture* ture;
    int w, h;
} LTexture;

LTexture guy = { NULL, 0, 0 };
LTexture background = { NULL, 0, 0 };

void free_texture(LTexture* obj) {
    if (obj != NULL) {
        SDL_DestroyTexture(obj->ture);
        obj->ture = NULL;
        obj->w = 0;
        obj->h = 0;
    }
}

void load_file(char* path, LTexture* obj) {
    free_texture(obj);
    SDL_Surface* loaded_surface = IMG_Load(path);
        
    if (loaded_surface == NULL) {
        printf("Cannot load image: %s %s\n", path, IMG_GetError());
    }

    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
    
    obj->ture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (obj->ture == NULL) {
        printf("Texture is null: %s\n", SDL_GetError());
    }
    
    obj->w = loaded_surface->w;
    obj->h = loaded_surface->h;
    
    SDL_FreeSurface(loaded_surface);
}

void render(int x, int y, LTexture* obj) {
    SDL_Rect render_quad = { x, y, obj->w, obj->h };
    SDL_RenderCopy(renderer, obj->ture, NULL, &render_quad);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Cannot initialize video: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("Color keying", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Can't create window: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Can't create renderer: %s\n", SDL_GetError());
    }
    

    load_file("foo.png", &guy);
    printf("w: %i, h: %i\n", guy.w, guy.h);
    load_file("background.png", &background);
    printf("w: %i, h: %i\n", background.w, background.h);

    SDL_Event e;
    int exit = 0;

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        render(0, 0, &background);
        render(480, 190, &guy);    

        SDL_RenderPresent(renderer);


        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    return 0;
        
}
