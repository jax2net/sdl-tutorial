#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "main.h"
#include "input.h"
#include "draw.h"
#include "constants.h"

App app;
Entity player;
Entity bullet;
PlayerState pstate;

void init(void);
void shutdown(void);

int main(int argc, char** argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    memset(&bullet, 0, sizeof(Entity));
    memset(&pstate, 0, sizeof(PlayerState));
    

    init();

    SDL_Texture* mike_texture = load_texture_from_file("../assets/mike.jpg", app.renderer);
    player.texture = mike_texture;
    player.x = 200;
    player.y = 200;

    SDL_Texture* bullet_texture = load_texture_from_file("../assets/bullet.png", app.renderer);
    bullet.texture = bullet_texture;

    while (1) {
        handle_input();

        if (pstate.up) player.y -= 4;
        if (pstate.down) player.y += 4;
        if (pstate.left) player.x -= 4;
        if (pstate.right) player.x += 4;

        // bullet
        if (pstate.fire && bullet.health == 0) {
            bullet.x = player.x;
            bullet.y = player.y;
            bullet.dx = 16;
            bullet.dy = 0;
            bullet.health = 1;
        }

        bullet.x += bullet.dx;
        bullet.y += bullet.dy;

        if (bullet.x > SCREEN_WIDTH) {
            bullet.health = 0;
        }

        SDL_SetRenderDrawColor(app.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(app.renderer);

        blit(player.texture, player.x, player.y);

        if (bullet.health > 0) {
            blit(bullet.texture, bullet.x, bullet.y);
        }

        SDL_RenderPresent(app.renderer);
        SDL_Delay(16);
    }

    shutdown();

    SDL_Quit();
    return 0;
}

void init(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialize image subsystem: %s\n", IMG_GetError());
    }

    if (TTF_Init() < 0) {
        printf("Failed to initialize TTF subsystem: %s\n", TTF_GetError());
    }
    
    app.window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (app.window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (app.renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
    }
}

void shutdown(void)
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);

    TTF_Quit();
    IMG_Quit();
    
}
