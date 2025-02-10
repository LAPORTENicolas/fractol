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
GREEN				= \033[92m
BLUE				= \033[94m
ORANGE			= \033[93m
RED					= \033[91m
WHITE				= \033[0m

all: mlx libft ${NAME}

${NAME}: ${OBJECTS}
	@${CC} ${OBJECTS} -L/${LIBFT} -lft -L${MLX} -lmlx_Linux -lXext -lX11 -lm -lz -o ${NAME}
	@echo -e "${GREEN}✅ Compilation termine"
	@echo -e ""
	@echo -e "For help try ./fractol -h 😉"

%.o: %.c
	@${CC} ${FLAGS} -I/${LIBFT} -I/${MLX} -O3 -g3 -c $< -o $@
	@echo -e "${BLUE}✅ Compilation $< objects termine"

libft:
	@if [ -d "${LIBFT}" ]; then \
		echo "⏳ Verification de libft ..."; \
		(cd libft && git pull > /dev/null 2>&1); \
	else \
		echo -e "${ORANGE}Pas de libft, telechargement ...${WHITE}"; \
		(git clone https://github.com/LAPORTENicolas/libft.git libft > /dev/null 2>&1); \
	fi
	@echo -e "${GREEN}✅ Libft, a jour !"; \
	echo -e "${WHITE}⏳ Compilation ..."; \
	${MAKE} -C ${LIBFT} > /dev/null
	@echo -e "${GREEN}✅ Compilation termine${WHITE}"; \
	echo -e ""; \

mlx:
	@if [ -d "${MLX}" ]; then \
		echo "⏳ Verification de mlx ..."; \
	else \
		echo "Installation de la MLX"; \
		(wget https://cdn.intra.42.fr/document/document/28246/minilibx-linux.tgz > /dev/null 2>&1); \
		(tar -xvsf minilibx-linux.tgz > /dev/null 2>&1); \
		(rm minilibx-linux.tgz > /dev/null 2>&1); \
		(mv minilibx-linux mlx > /dev/null 2>&1); \
	fi
	@echo -e "${GREEN}✅ MLX, a jour !"; \
	echo -e "${WHITE}⏳ Compilation ..."; \
	${MAKE} -s -C ${MLX} > /dev/null
	@echo -e "${GREEN}✅ Compilation termine${WHITE}"; \
	echo -e ""; \

clean:
	@echo -e "${ORANGE}⏳ Supression des objetcs fract-ol"
	@rm -rf ${OBJECTS}
	@echo -e "${ORANGE}⏳ Supression des objetcs libft et mlx"
	@if [ -d "${LIBFT}" ]; then \
		${MAKE} -C "${LIBFT}" clean > /dev/null 2>&1; \
	fi
	@if [ -d "${MLX}" ]; then \
		${MAKE} -C ${MLX} clean > /dev/null 2>&1; \
	fi

fclean: clean
	@echo -e "${ORANGE}⏳ Supression executale fract-ol"
	@rm -rf ${NAME}

reset:
	@echo -e "${RED}⏳ Supression des sources libft et mlx"
	@if [ -d "${LIBFT}" ]; then \
		rm -rf libft/ > /dev/null 2>&1; \
	fi
	@if [ -d "${MLX}" ]; then \
		rm -rf mlx/ > /dev/null 2>&1; \
	fi
	@echo -e "${ORANGE}⏳ Supression des object + executale fract-ol"
	@rm -rf ${OBJECTS}
	@rm -rf ${NAME}
	@echo -e "${GREEN}✅ Supression termine"

re: reset all

.PHONY: all clean fclean re
