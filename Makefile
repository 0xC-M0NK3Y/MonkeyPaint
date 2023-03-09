NAME = MonkeyPaint
CC = gcc
CFLAGS = -Wall -Wextra -O3
LDFLAGS = -lSDL2 -lSDL2_ttf
SRC = $(addprefix src/, main.c  inits.c  draw.c  menu.c  SDL_RenderDrawCircle.c  SDL_RenderFillCircle.c )
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME}: ${OBJ}
		${CC} ${OBJ} ${CFLAGS} ${INCLUDES} ${LDFLAGS} -o ${NAME}

%.o: %.c
		${CC} -c ${<} -o ${@} ${INCLUDES} ${CFLAGS}

clean:
		rm -rf ${OBJ} 

fclean: clean
		rm -rf ${NAME}

re : fclean all
