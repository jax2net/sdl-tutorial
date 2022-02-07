// template.c
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
const char* WINDOW_TITLE = "template.c";

typedef struct {
    SDL_Texture* texture;
    int w, h;
} GTexture;

// globals
SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
GTexture font_texture;
GTexture current_texture;

void init();
void shutdown();
void free_texture();

void render(int x, int y, GTexture texture) {
    SDL_Rect rect = { x, y, texture.w, texture.h };
    SDL_RenderCopy(renderer, texture.texture, NULL, &rect);
}

void load_from_file(char* path) {
    free_texture();
    SDL_Surface* tmp = IMG_Load(path);
    if (tmp == NULL) {
        printf("Cannot load surface from path: %s\n", IMG_GetError());
    }
    SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, tmp);
    if (result == NULL) {
        printf("Cannot create texture from surface: %s\n", SDL_GetError());
    }
    current_texture.texture = result;
    current_texture.w = tmp->w;
    current_texture.h = tmp->h;
    SDL_FreeSurface(tmp);
}

void setup_font(char* path, char* text, int size, GTexture* texture)
{
    font = TTF_OpenFont(path, size);
    if (font == NULL) {
        printf("Failed to open font: %s\n", TTF_GetError());
    }
    
    SDL_Color text_color = { 0, 0, 0 };
    SDL_Surface* tmp_surface = TTF_RenderText_Solid(font, text, text_color);
    if (tmp_surface == NULL) {
        printf("Can't render font: %s\n", TTF_GetError());
    }
    texture->texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    if (texture->texture == NULL) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }
    texture->w = tmp_surface->w;
    texture->h = tmp_surface->h;
    SDL_FreeSurface(tmp_surface);
}

int main() {
    init();

    SDL_Event e;
    int exit = 0;

    // setup texture
    setup_font("lazy.ttf", "This is a template file...", 40, &font_texture);
    
    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // render here
        render(50, 50, font_texture);

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

void free_texture() {
    if (current_texture.texture != NULL) {
        SDL_DestroyTexture(current_texture.texture);
        current_texture.texture = NULL;
        current_texture.w = 0;
        current_texture.h = 0;
    }
}
