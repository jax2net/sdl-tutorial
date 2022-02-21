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
        case SDL_MOUSEBUTTONDOWN:
            handle_mouse_down(&e);
            break;
        case SDL_MOUSEBUTTONUP:
            handle_mouse_up(&e);
            break;
        default:
            break;
        }
    }
}
    
void handle_key_down(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_W) {
            app.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S) {
            app.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A) {
            app.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D) {
            app.right = 1;
        }
    }
}

void handle_key_up(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_W) {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S) {
            app.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A) {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D) {
            app.right = 0;
        }
    }
}


void handle_mouse_down(SDL_MouseButtonEvent* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        app.fire = 1;
    }
}

void handle_mouse_up(SDL_MouseButtonEvent* event)
{
    if (event->type == SDL_MOUSEBUTTONUP) {
        app.fire = 0;
    }
}
