#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "inits.h"
#include "draw.h"
#include "menu.h"

int main(int argc, char **argv)
{
	env_t		env;
	SDL_Event	*event = &env.sdl.event;
	param_t		*param = &env.param;
	char buffer[5] = {0};
	int i = 0;

	(void)argc;
	(void)argv;
	if (init_paint(&env) < 0)
		return EXIT_FAILURE;
	while (param->running)
	{
		while (SDL_PollEvent(event))
        {
			if (env.drawer.on_size_input && event->type == SDL_TEXTINPUT) {
				strcat(buffer, event->text.text);
				char *tmp = strchr(buffer, '*');
				if (tmp != NULL) {
					tmp[0] = '\0';
					int size = atoi(buffer);
					if (size > 0)
						env.drawer.size = size;
					memset(buffer, 0, sizeof(buffer));
					i = 0;
					draw(&env.sdl, &env.drawer, &env.menu);
				} else {
					i++;
					if ((long unsigned int)i >= sizeof(buffer)-1) {
						memset(buffer, 0, sizeof(buffer));
						i = 0;
					}
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
				env.drawer.on_size_input = FALSE;
				if (env.drawer.pos.x > WIN_WIDTH-MENU_SIZE) {			
					if (menu_click(&env.menu, &env.drawer) > 0) {
						env.menu.clicked = TRUE;
						draw(&env.sdl, &env.drawer, &env.menu);
					}
				}
			}
			if (event->button.type == SDL_MOUSEMOTION && event->button.button == SDL_BUTTON_LEFT) {
				env.drawer.on_size_input = FALSE;
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