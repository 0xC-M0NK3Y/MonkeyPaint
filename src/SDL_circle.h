#ifndef SDL_circle_h_
#define SDL_circle_h_

#include <SDL2/SDL.h>

int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);

#endif /* SDL_circle_h_ */
