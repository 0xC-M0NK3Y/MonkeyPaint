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

	(void)argc;
	(void)argv;
	if (init_paint(&env) < 0)
		return EXIT_FAILURE;
	//TODO: ici
	env.drawer.color = GREEN;
	env.drawer.form = FORM_RECT;
	env.drawer.size = 20;
	while (param->running)
	{
		while (SDL_PollEvent(event))
        {
            if (event->type == SDL_KEYDOWN) {
                switch (event->key.keysym.sym) {
                    case SDLK_ESCAPE: param->running = FALSE; break;
                    default: break;
                }
            }
			if (event->button.type == SDL_MOUSEBUTTONDOWN) {
				SDL_GetMouseState(&env.drawer.pos.x, &env.drawer.pos.y);
				if (env.drawer.pos.x > WIN_WIDTH-MENU_SIZE) {			
					menu_click(&env.menu, &env.drawer);
				}
			}
			if (event->button.type == SDL_MOUSEMOTION && event->button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&env.drawer.pos.x, &env.drawer.pos.y);
				if (env.drawer.pos.x < WIN_WIDTH-MENU_SIZE) {
					draw(&env.sdl, &env.drawer, &env.menu);
				}
			}
            if (event->type == SDL_QUIT)
                param->running = FALSE;
        }
	}
	SDL_Quit();
	return 0;
}