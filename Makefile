NAME = TimPaint
CC = gcc
CFLAGS = -Wall -Wextra -O3 -g
INCLUDES = -I/Users/tescande/.brew/Cellar/sdl2/2.26.3/include/ -D_THREAD_SAFE
LDFLAGS = -L/Users/tescande/.brew/Cellar/sdl2/2.26.3/lib /Users/tescande/.brew/Cellar/sdl2/2.26.3/lib/libSDL2.a -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
SRC = $(addprefix src/, main.c  inits.c  draw.c  menu.c )
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
