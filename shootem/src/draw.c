// draw.c
#include "draw.h"
#include "main.h"

SDL_Texture* load_texture_from_file(char* path)
{
    SDL_Texture *result;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);

    result = IMG_LoadTexture(app.renderer, path);
    
    return result;
}

void blit(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.w = 75;
    dest.h = 75;
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
