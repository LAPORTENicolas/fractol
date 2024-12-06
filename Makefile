# LIBFT
SOURCES			= main.c \
							src/utils/color_utils.c src/utils/color_palette.c src/utils/color_palette2.c \
							src/utils/fun_utils.c src/utils/args_utils.c src/utils/ssaa.c src/utils/args_utils2.c \
							src/env_manager.c src/complex_utils.c \
							src/vec/vec2.c src/vec/vec3.c \
							src/input/keyboard_manager.c src/input/mouse_manager.c \
							src/sets/mandelbrot.c src/sets/julia.c src/sets/burning_ship.c src/sets/buddhabrot.c \
							src/sets/nova.c src/sets/newton.c \
							src/args_manager.c export.c
OBJECTS     = ${SOURCES:.c=.o}
NAME        = fractol
CC          = cc
FLAGS       = -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${OBJECTS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Lft -lft -Ift -o ${NAME}

%.o: %.c
	${CC} ${FLAGS} -I/usr/include -Imlx_linux -O3 -Ift -g3 -c $< -o $@

clean:
	rm -rf ${OBJECTS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
