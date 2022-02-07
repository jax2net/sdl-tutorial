// draw.c
#include "draw.h"

SDL_Texture* load_texture_from_file(char* path, SDL_Renderer* renderer) {
    SDL_Texture *result;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);

    result = IMG_LoadTexture(renderer, path);
    
    return result;
}

void blit(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}
