#include "structs.h"

static inline int click_on(const pos_t *pos, const SDL_Rect *rect) {
	return (pos->x >= rect->x && pos->x <= rect->x + rect->w && pos->y >= rect->y && pos->y <= rect->y + rect->h);
}

int menu_click(const menu_t *menu, drawer_t *drawer) {
	for (int i = 0; i < MENU_COLORS_NUMBER; i++) {
		if (click_on(&drawer->pos, &menu->colors[i])) {
			switch (i) {
			case MENU_RED: drawer->color = RED; break;
			case MENU_BLUE: drawer->color = BLUE; break;
			case MENU_GREEN: drawer->color = GREEN; break;
			case MENU_YELLOW: drawer->color = YELLOW; break;
			case MENU_CYAN: drawer->color = CYAN; break;
			case MENU_MAGENTA: drawer->color = MAGENTA; break;
			case MENU_WHITE: drawer->color = WHITE; break;
			case MENU_BLACK: drawer->color = BLACK; break;
			default: break;
			}
			return 1;
		}
	}
	for (int i = 0; i < FORMS_NUMBER; i++) {
		if (click_on(&drawer->pos, &menu->forms[i])) {
			switch (i) {
			case FORM_POINT: drawer->form = FORM_POINT; break;
			case FORM_CIRCLE: drawer->form = FORM_CIRCLE; break;
			case FORM_RECT: drawer->form = FORM_RECT; break;
			default: break;
			}
		}
	}
	if (click_on(&drawer->pos, &menu->size_input))
		drawer->on_size_input = TRUE;
	if (click_on(&drawer->pos, &menu->red))
		drawer->on_red_input = TRUE;
	if (click_on(&drawer->pos, &menu->blue))
		drawer->on_blue_input = TRUE;
	if (click_on(&drawer->pos, &menu->green))
		drawer->on_green_input = TRUE;
	return 1;
}