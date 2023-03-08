#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "structs.h"
#include "defines.h"
#include "draw.h"

static int init_menu(sdlenv_t *sdl, menu_t *menu) {
	for (int i = 0; i < MENU_COLORS_NUMBER; i++) {
		if (i % 2 == 0)
			menu->colors[i].x = WIN_WIDTH-MENU_SIZE + MENU_SIZE/4;
		else
			menu->colors[i].x = WIN_WIDTH-MENU_SIZE + MENU_SIZE/4*2;
		if (i % 2 == 0)
			menu->colors[i].y = 0 + WIN_HEIGHT/20*(i+1);
		else
			menu->colors[i].y = 0 + WIN_HEIGHT/20*(i);
		menu->colors[i].w = MENU_SIZE/8;
		menu->colors[i].h = MENU_SIZE/8;
	}

	draw_menu(sdl, menu);
	return 1;
}

static int init_window(sdlenv_t *sdl, menu_t *menu) {
	/* on render dans notre texture */
	SDL_SetRenderTarget(sdl->renderer, sdl->display);
	/* on dessine le fond en blanc */
    SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(WHITE));
	/* on creer le canvas */
	const SDL_Rect rect = {.x = 0, .y = 0, .w = WIN_WIDTH-MENU_SIZE, .h = WIN_HEIGHT};
	sdl->canvas = rect;
	/* on le rempli en blanc */
	SDL_RenderFillRect(sdl->renderer, &sdl->canvas);
	/* on rendere dans la fenetre */
	SDL_SetRenderTarget(sdl->renderer, NULL);
	/* on dessine en noir */
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(MENU_COLOR));
	/* on rempli en noir */
    SDL_RenderClear(sdl->renderer);
	/* on dessine le menu */
	init_menu(sdl, menu);
	/* on dessine le canvas blanc dessus */
	SDL_RenderCopyEx(sdl->renderer, sdl->display, NULL, &sdl->canvas, 0, NULL, SDL_FLIP_NONE);
	/* on commit */
    SDL_RenderPresent(sdl->renderer);
	return 1;
}
 
static int init_sdl(sdlenv_t *sdl) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return -__LINE__;
    sdl->window_flag = SDL_WINDOW_SHOWN; //| SDL_WINDOW_BORDERLESS;
    sdl->window = SDL_CreateWindow("TimPaint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, sdl->window_flag);
    if (sdl->window == NULL)
        return -__LINE__;
    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
    if (sdl->renderer == NULL)
        return -__LINE__;
	sdl->display = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH-MENU_SIZE, WIN_HEIGHT);
	if (sdl->display == NULL)
		return -__LINE__;
    return 1;
}

int init_paint(env_t *env) {

	memset(env, 0, sizeof(*env));

	if (init_sdl(&env->sdl) < 0)
		return fprintf(stderr, "ERROR INIT SDL\n"), -1;
	init_window(&env->sdl, &env->menu);
	env->param.running = TRUE;
    SDL_GetWindowSize(env->sdl.window, &env->param.width, &env->param.height);
    return 1;
}