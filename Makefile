CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I includes
NAME = cub3d

SRC = src/main.c src/parse_map.c src/parse_map2.c src/parse_header.c \
      src/map_parse_utils.c src/free_utils.c src/map_control_functions.c \
      src/error.c \
      external/get_next_line.c external/get_next_line_utils.c \
      src/mlx_functions/mlx_init.c

LIBS = external/libft/libft.a

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) external/libft/libft.a $(MLX_FLAGS) -I includes -o cub3d

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re