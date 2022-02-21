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
            pstate.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S) {
            pstate.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A) {
            pstate.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D) {
            pstate.right = 1;
        }
    }
}

void handle_key_up(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0) {
        if (event->keysym.scancode == SDL_SCANCODE_W) {
            pstate.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S) {
            pstate.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A) {
            pstate.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D) {
            pstate.right = 0;
        }
    }
}


void handle_mouse_down(SDL_MouseButtonEvent* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        pstate.fire = 1;
    }
}

void handle_mouse_up(SDL_MouseButtonEvent* event)
{
    if (event->type == SDL_MOUSEBUTTONUP) {
        pstate.fire = 0;
    }
}
