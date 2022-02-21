#ifndef MAIN_H
#define MAIN_H
#include "common.h"

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture *texture;
} Entity;

typedef struct {
    int up;
    int down;
    int left;
    int right;
    int fire;
} PlayerState;

// globals for being used across the game
extern App app;
extern Entity player;
extern PlayerState pstate;

#endif //MAIN_H
