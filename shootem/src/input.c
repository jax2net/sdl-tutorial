#include "common.h"
#include "input.h"
#include "main.h"

void handle_input(void)
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            handle_key_down(&e);
            break;
        case SDL_KEYUP:
            handle_key_up(&e);
            break;
        default:
            break;
        }
    }
}
    
void handle_key_down(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            app.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            app.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            app.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            app.right = 1;
        }
    }
}

void handle_key_up(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_UP) {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
            app.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
            app.right = 0;
        }
    }
}
