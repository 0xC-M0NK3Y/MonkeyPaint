#ifndef DEFINES_H
# define DEFINES_H

#include <stdint.h>

#define WIN_WIDTH	1600
#define WIN_HEIGHT	920

typedef uint32_t	flag_t;
typedef uint32_t	color_t;

#define TRUE	1
#define FALSE	0

#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF
#define YELLOW	0xFFFF00FF
#define MAGENTA	0xFF00FFFF
#define CYAN	0x00FFFFFF
#define WHITE	0xFFFFFFFF
#define BLACK	0x000000FF

#define MENU_COLOR	0x505050FF

#define GET_COLOR(color) \
			((color >> 24) & 0xFF), \
			((color >> 16) & 0xFF), \
			((color >> 8) & 0xFF),  \
			((color >> 0) & 0xFF)

#define MENU_SIZE	(WIN_WIDTH*0.13)

#endif