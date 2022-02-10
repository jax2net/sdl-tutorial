#ifndef MAIN_H
#define MAIN_H
#include "common.h"

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    int up;
    int down;
    int left;
    int right;
} App;

typedef struct {
    int x;
    int y;
    SDL_Texture *texture;
} Entity;

// globals for being used across the game
extern App app;
extern Entity player;

#endif //MAIN_H
