# LIBFT
SOURCES			= main.c \
							src/utils/color_utils.c src/utils/color_palette.c \
							src/utils/fun_utils.c src/utils/args_utils.c src/utils/ssaa.c src/utils/args_utils2.c \
							src/utils/args_utils3.c src/utils/fun_utils2.c \
							src/env_manager.c src/complex_utils.c \
							src/vec/vec2.c src/vec/vec3.c \
							src/input/keyboard_manager.c src/input/mouse_manager.c \
							src/sets/mandelbrot.c src/sets/julia.c src/sets/burning_ship.c src/sets/buddhabrot.c \
							src/sets/newton.c src/sets/nova.c \
							src/args_manager.c src/utils/img_utils.c export.c \
							src/utils/keyboard_utils.c
OBJECTS     = ${SOURCES:.c=.o}
NAME        = fractol
CC          = cc
FLAGS       = -Wall -Werror -Wextra
LIBFT				= libft/
MLX					= mlx/

all: mlx libft ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${OBJECTS} -Lft -lft -Lmlx -lmlx_Linux -lXext -lX11 -lm -lz -Lft -lft -Ift -o ${NAME}

%.o: %.c
	${CC} ${FLAGS} -Ift -Imlx -O3 -Ift -g3 -c $< -o $@

libft:
	@if [ -d "${LIBFT}" ]; then \
		cd libft && git pull; \
	else \
		git clone https://github.com/LAPORTENicolas/libft.git libft; \
	fi
	${MAKE} -C ${LIBFT}

mlx:
	@if [ -d "${MLX}" ]; then \
		cd libft && git pull; \
	else \
		wget https://cdn.intra.42.fr/document/document/28246/minilibx-linux.tgz; \
		tar -xvsf minilibx-linux.tgz; \
		rm minilibx-linux.tgz; \
		mv minilibx-linux mlx; \
	fi
	${MAKE} -C ${MLX}

clean:
	rm -rf ${OBJECTS}
	${MAKE} -C ${LIBFT} clean
	${MAKE} -C ${MLX} clean

fclean: clean
	rm -rf ${NAME}
	${MAKE} -C ${LIBFT} fclean
	${MAKE} -C ${MLX} clean

reset:
	rm -rf libft/
	rm -rf mlx/
	rm -rf ${OBJECTS}

re: fclean all

.PHONY: all clean fclean re libft
