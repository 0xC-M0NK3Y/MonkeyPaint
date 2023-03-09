#include <math.h>

#include "structs.h"
#include "SDL_circle.h"


static int draw_rect(const sdlenv_t *sdl, const drawer_t *drawer) {
	const SDL_Rect rect = {.x = drawer->pos.x - drawer->size/2, .y = drawer->pos.y - drawer->size/2, .w = drawer->size, .h = drawer->size};
	SDL_RenderFillRect(sdl->renderer, &rect);
	return 1;
}

static int draw_point(const sdlenv_t *sdl, const drawer_t *drawer) {
	SDL_RenderFillCircle(sdl->renderer, drawer->pos.x, drawer->pos.y, 2);
	return 1;
}

static int draw_circle(const sdlenv_t *sdl, const drawer_t *drawer) {
	SDL_RenderFillCircle(sdl->renderer, drawer->pos.x, drawer->pos.y, drawer->size/2);
	return 1;
}

static int draw_size_input(const sdlenv_t *sdl, const menu_t *menu, const drawer_t *drawer) {
    SDL_Surface *tmp;
    char str[11] = {0};
	SDL_Color color = {.a = 0xFF, .b = 0x0, .g = 0x0, .r = 0x0};

	snprintf(str, 10, "%d", drawer->size);
	tmp = TTF_RenderText_Solid(menu->font, str, color);
	if (tmp == NULL)
		return -1;
	SDL_Texture *text = SDL_CreateTextureFromSurface(sdl->renderer, tmp);
	SDL_RenderCopyEx(sdl->renderer, text, NULL, &menu->size_input, 0, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(tmp);
	return 1;
}

int draw_menu(const sdlenv_t *sdl, const menu_t *menu, const drawer_t *drawer) {
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
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(WHITE));
	for (int i = 0; i < FORMS_NUMBER; i++) {
		switch (i) {
		case FORM_POINT: SDL_RenderFillCircle(sdl->renderer, menu->forms[i].x+menu->forms[i].w/2, menu->forms[i].y+menu->forms[i].h/2, 2); break;
		case FORM_RECT: SDL_RenderFillRect(sdl->renderer, &menu->forms[i]); break;
		case FORM_CIRCLE: SDL_RenderFillCircle(sdl->renderer, menu->forms[i].x+menu->forms[i].w/2, menu->forms[i].y+menu->forms[i].h/2, menu->forms[i].w/2); break;
		default: break;
		}
	}
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(WHITE));
	SDL_RenderFillRect(sdl->renderer, &menu->size_input);
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(drawer->color));
	switch (drawer->form) {
	case FORM_CIRCLE: SDL_RenderFillCircle(sdl->renderer, menu->actual_color.x+menu->actual_color.w/2, menu->actual_color.y, 10); break;
	case FORM_RECT: SDL_RenderFillRect(sdl->renderer, &menu->actual_color); break;
	case FORM_POINT: SDL_RenderFillCircle(sdl->renderer, menu->actual_color.x+menu->actual_color.w/2, menu->actual_color.y, 2); break;
	default: break;
	}
	draw_size_input(sdl, menu, drawer);
	return 1;
}

int draw(const sdlenv_t *sdl, const drawer_t *drawer, const menu_t *menu) {
	SDL_SetRenderTarget(sdl->renderer, sdl->display);
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(drawer->color));

	if (menu->clicked == FALSE) {
		switch (drawer->form) {
		case FORM_POINT:	draw_point(sdl, drawer); break;
		case FORM_RECT:		draw_rect(sdl, drawer); break;
		case FORM_CIRCLE:	draw_circle(sdl, drawer); break;
		default: break;
		}
	}
	SDL_SetRenderTarget(sdl->renderer, NULL);
	SDL_SetRenderDrawColor(sdl->renderer, GET_COLOR(MENU_COLOR));
	SDL_RenderClear(sdl->renderer);
	draw_menu(sdl, menu, drawer);
	SDL_RenderCopyEx(sdl->renderer, sdl->display, NULL, &sdl->canvas, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(sdl->renderer);
	return 1;
}