#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "inits.h"
#include "draw.h"
#include "menu.h"

static void reset_inputs(drawer_t *drawer, char *buffer) {
	drawer->on_size_input = FALSE;
	drawer->on_red_input = FALSE;
	drawer->on_blue_input = FALSE;
	drawer->on_green_input = FALSE;
	memset(buffer, 0, BUFFER_SIZE);
}

static void read_input_size(env_t *env, char *buffer, int *i, SDL_Event *event) {
	strcat(buffer, event->text.text);
	char *tmp = strchr(buffer, '*');
	if (tmp != NULL) {
		tmp[0] = '\0';
		int size = atoi(buffer);
		if (size > 0)
			env->drawer.size = size;
		memset(buffer, 0, sizeof(BUFFER_SIZE));
		i[0] = 0;
		draw(&env->sdl, &env->drawer, &env->menu);
	} else {
		i[0]++;
		if ((long unsigned int)i[0] >= BUFFER_SIZE-1) {
			memset(buffer, 0, sizeof(BUFFER_SIZE));
			i[0] = 0;
		}
	}
}

void read_color_input(env_t *env, char *buffer, int *i, SDL_Event *event, color_t color) {
	strcat(buffer, event->text.text);
	char *tmp = strchr(buffer, '*');
	if (tmp != NULL) {
		tmp[0] = '\0';
		int size = atoi(buffer);
		if (isdigit(buffer[0]) && size >= 0x0 && size <= 0xFF) {
			switch (color) {
			case RED: env->drawer.color = (size << 24) | (env->drawer.color & 0x00FFFFFF); break;
			case BLUE: env->drawer.color = (size << 16) | (env->drawer.color & 0xFF00FFFF); break;
			case GREEN: env->drawer.color = (size << 8) | (env->drawer.color & 0xFFFF00FF); break;
			default: break;
			}
		}
		memset(buffer, 0, sizeof(BUFFER_SIZE));
		i[0] = 0;
		draw(&env->sdl, &env->drawer, &env->menu);
	} else {
		i[0]++;
		if ((long unsigned int)i[0] >= BUFFER_SIZE-1) {
			memset(buffer, 0, sizeof(BUFFER_SIZE));
			i[0] = 0;
		}
	}
}

int main(int argc, char **argv)
{
	env_t		env;
	SDL_Event	*event = &env.sdl.event;
	param_t		*param = &env.param;
	char buffer[BUFFER_SIZE] = {0};
	int i = 0;

	(void)argc;
	(void)argv;
	if (init_paint(&env) < 0)
		return EXIT_FAILURE;
	while (param->running)
	{
		while (SDL_PollEvent(event))
        {
			if (event->type == SDL_TEXTINPUT) {
				if (env.drawer.on_size_input) {
					read_input_size(&env, buffer, &i, event);
				} else if (env.drawer.on_red_input) {
					read_color_input(&env, buffer, &i, event, RED);
				} else if (env.drawer.on_blue_input) {
					read_color_input(&env, buffer, &i, event, BLUE);
				} else if (env.drawer.on_green_input) {
					read_color_input(&env, buffer, &i, event, GREEN);
				}
			}
            if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                    case SDLK_ESCAPE: param->running = FALSE; break;
                    default: break;
                }
            }
			if (event->button.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&env.drawer.pos.x, &env.drawer.pos.y);
				reset_inputs(&env.drawer, buffer);
				if (env.drawer.pos.x > WIN_WIDTH-MENU_SIZE) {			
					if (menu_click(&env.menu, &env.drawer) > 0) {
						env.menu.clicked = TRUE;
						draw(&env.sdl, &env.drawer, &env.menu);
					}
				}
			}
			if (event->button.type == SDL_MOUSEMOTION && event->button.button == SDL_BUTTON_LEFT) {
				reset_inputs(&env.drawer, buffer);
				env.menu.clicked = FALSE;
				SDL_GetMouseState(&env.drawer.pos.x, &env.drawer.pos.y);
				if (env.drawer.pos.x < WIN_WIDTH-MENU_SIZE) {
					draw(&env.sdl, &env.drawer, &env.menu);
				}
			}
            if (event->type == SDL_QUIT)
                param->running = FALSE;
        }
		SDL_Delay(15);
	}
	SDL_Quit();
	return 0;
}