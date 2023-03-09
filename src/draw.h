#ifndef DRAW_H
# define DRAW_H

#include "structs.h"

int draw(const sdlenv_t *sdl, const drawer_t *drawer, const menu_t *menu);
int draw_menu(const sdlenv_t *sdl, const menu_t *menu, const drawer_t *drawer);

#endif