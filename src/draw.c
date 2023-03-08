

#include "structs.h"
/*
static int draw_circle(sdlenv_t *sdl,const drawer_t *drawer) {
	return 1;
}*/

static int draw_rect(sdlenv_t *sdl, const drawer_t *drawer) {
	const SDL_Rect rect = {.x = drawer->pos.x - drawer->size/2, .y = drawer->pos.y - drawer->size/2, .w = drawer->size, .h = drawer->size};
	SDL_RenderFillRect(sdl->renderer, &rect);
	return 1;
}

static int draw_point(sdlenv_t *sdl, const drawer_t *drawer) {
	SDL_RenderDrawPoint(sdl->renderer, drawer->pos.x, drawer->pos.y);
	return 1;
}

int draw_menu(sdlenv_t *sdl, const menu_t *menu) {
	for (int i = 0; i < MENU_COLORS_NUMBER; i++) {
		color_t	color = 0;
		switch (i) {
		case MENU_RED: color = RED; break;
		case MENU_BLUE: color = BLUE; break;
		case MENU_GREEN: color = GREEN; break;
		case MENU_YELLOW: color = YELLOW; break;
		case MENU_CYAN: color = CYAN; break;
		case MENU_MAGENTA: color = MAGENTA; break;
		case MENU_WHITE: color = WHITE; break;
		case MENU_BLACK: color = BLACK; break;
		default: break;
		}
		SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(color));
		SDL_RenderFillRect(sdl->renderer, &menu->colors[i]);
	}
	return 1;
}

int draw(sdlenv_t *sdl, const drawer_t *drawer, const menu_t *menu) {
	SDL_SetRenderTarget(sdl->renderer, sdl->display);
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(drawer->color));

	switch (drawer->form) {
	case FORM_POINT:	draw_point(sdl, drawer); break;
	case FORM_RECT:		draw_rect(sdl, drawer); break;
	default: break;
	}
	SDL_SetRenderTarget(sdl->renderer, NULL);
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(MENU_COLOR));
	SDL_RenderClear(sdl->renderer);
	draw_menu(sdl, menu);
	SDL_RenderCopyEx(sdl->renderer, sdl->display, NULL, &sdl->canvas, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(sdl->renderer);
	return 1;
}