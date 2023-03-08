#ifndef STRUCTS_H
# define STRUCTS_H

#include <SDL2/SDL.h>

#include "defines.h"

typedef struct pos {
	int x;
	int y;
}	pos_t;

typedef enum form {
	FORM_POINT,
	FORM_RECT,
	FORM_CIRCLE,
	FORM_TRIANGLE,
	FORMS_NUMBER
}	form_e;

typedef struct drawer {
	pos_t		pos;
	color_t		color;
	uint32_t	size;
	form_e		form;
}	drawer_t;

typedef struct sdlenv {
    SDL_Window      *window;     // fenetre
    SDL_Renderer    *renderer;   // rendrerer
    SDL_Event       event;       // evenements
	SDL_Texture 	*display;
	SDL_Rect		canvas;
    flag_t          window_flag; // flag de la fenetre
}   sdlenv_t;

typedef enum menu_colors {
	MENU_RED,
	MENU_GREEN,
	MENU_BLUE,
	MENU_YELLOW,
	MENU_MAGENTA,
	MENU_CYAN,
	MENU_WHITE,
	MENU_BLACK,
	MENU_COLORS_NUMBER
}	menu_colors_e;

typedef struct menu {
	SDL_Rect	colors[MENU_COLORS_NUMBER];
	SDL_Rect	forms[FORMS_NUMBER];
}	menu_t;

typedef struct param {
    int running;
    int fullscreen;
    int width;
    int height;
}	param_t;

typedef struct env {
	sdlenv_t	sdl;
	param_t		param;
	drawer_t	drawer;
	menu_t		menu;
}	env_t;

#endif