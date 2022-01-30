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

SDL_Rect clips[4];

typedef struct {
    SDL_Texture* ture;
    int w, h;
} LTexture;

void free_texture(LTexture* obj) {
    if (obj != NULL) {
        SDL_DestroyTexture(obj->ture);
        obj->ture = NULL;
        obj->w = 0;
        obj->h = 0;
    }
}

void init_clips() {
    // top left
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = 100;
    clips[0].h = 100;

    // top right
    clips[1].x = 100;
    clips[1].y = 0;
    clips[1].w = 100;
    clips[1].h = 100;

    // bottom left
    clips[2].x = 0;
    clips[2].y = 100;
    clips[2].w = 100;
    clips[2].h = 100;

    // bottom right
    clips[3].x = 100;
    clips[3].y = 100;
    clips[3].w = 100;
    clips[3].h = 100;
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

void render(int x, int y, LTexture* obj, SDL_Rect* clip) {
    SDL_Rect render_quad = { x, y, obj->w, obj->h };

    // clip rendering dimensions
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    
    SDL_RenderCopy(renderer, obj->ture, clip, &render_quad);
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


    LTexture dots_texture = { NULL, 0, 0 };
    load_file("dots.png", &dots_texture);
    init_clips();

    SDL_Event e;
    int exit = 0;

    while (!exit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { exit = 1; }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);


        // render here
        render(0, 0, &dots_texture, &clips[0]);
        render(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, &dots_texture, &clips[3]);
        
        
        SDL_RenderPresent(renderer);


        
    }

    // shutdown subsystems
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    SDL_Quit();
    return 0;
        
}
