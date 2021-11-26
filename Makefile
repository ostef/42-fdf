NAME = fdf
SRC_FILES = source/main.c source/draw.c source/time.c source/map.c \
	source/mat4f/axis_angle.c source/mat4f/identity.c source/mat4f/multiply.c\
	source/mat4f/ortho.c source/mat4f/perspective.c source/mat4f/translate.c source/mat4f/transpose.c\
	source/vec3f/add_sub_mul.c source/vec3f/normalize.c source/vec3f/vec3f.c\
	source/vec2f/add_sub_mul.c source/vec2f/normalize.c source/vec2f/vec2f.c
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_FILES = fdf.h
INCLUDE_DIRS = libft mlx .
LIB_DIRS = libft mlx
LIBS = ft mlx
CC = gcc
C_FLAGS = $(addprefix -I, $(INCLUDE_DIRS)) -Wall -Wextra -Werror -O3

all: $(NAME)

$(OBJ_FILES): %.o: %.c $(INCLUDE_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME): libft mlx $(OBJ_FILES)
	$(CC) $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS)) -framework OpenGL -framework AppKit $(OBJ_FILES) -o $(NAME)

libft:
	make -C libft

mlx:
	make -C mlx
	cp mlx/libmlx.dylib .

fclean_libs:
	make -C libft fclean
	make -C mlx fclean

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f libmlx.dylib
	rm -f $(NAME)

re: fclean all

.PHONY: all libft mlx clean fclean
