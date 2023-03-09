#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "defines.h"
#include "draw.h"

static int init_drawer(drawer_t *drawer) {
	drawer->color = GREEN;
	drawer->form = FORM_CIRCLE;
	drawer->size = 10;
	drawer->on_size_input = FALSE;
	return 1;
}

static int init_menu(sdlenv_t *sdl, menu_t *menu, const drawer_t *drawer) {
	for (int i = 0; i < MENU_COLORS_NUMBER; i++) {
		if (i % 2 == 0)
			menu->colors[i].x = WIN_WIDTH-MENU_SIZE + MENU_SIZE/3;
		else
			menu->colors[i].x = WIN_WIDTH-MENU_SIZE + MENU_SIZE/3*2;
		if (i % 2 == 0)
			menu->colors[i].y = 0 + WIN_HEIGHT/20*(i+1);
		else
			menu->colors[i].y = 0 + WIN_HEIGHT/20*(i);
		menu->colors[i].w = MENU_SIZE/8;
		menu->colors[i].h = MENU_SIZE/8;
	}
	for (int i = 0; i < FORMS_NUMBER; i++) {
		menu->forms[i].x = WIN_WIDTH-MENU_SIZE + (MENU_SIZE/4*(i+1));
		menu->forms[i].y = menu->colors[MENU_COLORS_NUMBER-1].y + WIN_HEIGHT/8;
		menu->forms[i].w = MENU_SIZE/8;
		menu->forms[i].h = MENU_SIZE/8;
	}
	menu->size_input.x = WIN_WIDTH-MENU_SIZE+MENU_SIZE/4;
	menu->size_input.y = menu->forms[FORMS_NUMBER-1].y + WIN_HEIGHT/8;
	menu->size_input.w = MENU_SIZE-MENU_SIZE/3;
	menu->size_input.h = 30;
	menu->red.x = WIN_WIDTH-MENU_SIZE+MENU_SIZE/3*0+MENU_SIZE/20;
	menu->red.y = menu->size_input.y + WIN_HEIGHT/8;
	menu->red.w = MENU_SIZE/3-MENU_SIZE/10;
	menu->red.h = 30;
	menu->blue.x = WIN_WIDTH-MENU_SIZE+MENU_SIZE/3*1+MENU_SIZE/20;
	menu->blue.y = menu->size_input.y + WIN_HEIGHT/8;
	menu->blue.w = MENU_SIZE/3-MENU_SIZE/10;
	menu->blue.h = 30;
	menu->green.x = WIN_WIDTH-MENU_SIZE+MENU_SIZE/3*2+MENU_SIZE/20;
	menu->green.y = menu->size_input.y + WIN_HEIGHT/8;
	menu->green.w = MENU_SIZE/3-MENU_SIZE/10;
	menu->green.h = 30;
	menu->font = TTF_OpenFont("ressources/fonts/comicate.ttf", 50);
	if (menu->font == NULL)
		return -__LINE__;
	menu->actual_color.x = WIN_WIDTH-MENU_SIZE/2-10;
	menu->actual_color.y = WIN_HEIGHT - WIN_HEIGHT/20;
	menu->actual_color.w = 40;
	menu->actual_color.h = 40;
	draw_menu(sdl, menu, drawer);
	return 1;
}

static int init_window(sdlenv_t *sdl, menu_t *menu, const drawer_t *drawer) {
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
	init_menu(sdl, menu, drawer);
	/* on dessine le canvas blanc dessus */
	SDL_RenderCopyEx(sdl->renderer, sdl->display, NULL, &sdl->canvas, 0, NULL, SDL_FLIP_NONE);
	/* on commit */
    SDL_RenderPresent(sdl->renderer);
	return 1;
}
 
static int init_sdl(sdlenv_t *sdl) {
	SDL_StartTextInput();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -__LINE__;
	if (TTF_Init() < 0)
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
	init_drawer(&env->drawer);
	init_window(&env->sdl, &env->menu, &env->drawer);
	env->param.running = TRUE;
    SDL_GetWindowSize(env->sdl.window, &env->param.width, &env->param.height);
    return 1;
}