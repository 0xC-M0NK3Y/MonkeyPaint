#include <SDL2/SDL.h>

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
	int x_center = x;
	int y_center = y;
	x = 0;
	y = radius;
	int m = 5 - 4 * radius;

	while (x <= y)
	{
        const SDL_Point points[8] = {
                {.x = -x+x_center, .y = y+y_center},
                {.x = -x+x_center, .y = -y+y_center},
                {.x = x+x_center,  .y = y+y_center},
                {.x = x+x_center,  .y = -y+y_center},
                {.x = y+x_center,  .y = x+y_center},
                {.x = -y+x_center, .y = x+y_center},
                {.x = y+x_center,  .y = -x+y_center},
                {.x = -y+x_center, .y = -x+y_center}};
        int r = SDL_RenderDrawLines(renderer, points, 8);
        if (r < 0)
            return r;
		if (m > 0) {
			y = y - 1;
			m = m - 8*y;
		}
		x++;
		m = m + 8*x + 4;
	}
	return 1;
}