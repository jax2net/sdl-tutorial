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
    int fire;
} App;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture *texture;
} Entity;

// globals for being used across the game
extern App app;
extern Entity player;

#endif //MAIN_H
