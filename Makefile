CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
INCLUDES = -I includes -I src/mlx_functions -I $(MLX_DIR)
NAME = cub3d

SRC = src/main.c src/parse_map.c src/parse_map2.c src/parse_header.c \
      src/map_parse_utils.c src/free_utils.c src/map_control_functions.c \
      src/error.c \
      external/get_next_line.c external/get_next_line_utils.c \
      src/mlx_functions/mlx_init.c src/init_player.c

LIBS = external/libft/libft.a

all: mlx $(NAME)

mlx:
	@make -C $(MLX_DIR) 2>/dev/null || true

$(LIBS):
	@make -C external/libft

$(NAME): $(LIBS)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

clean:
	@rm -f $(NAME)
	@make -C external/libft clean 2>/dev/null || true

fclean: clean
	@make -C external/libft fclean 2>/dev/null || true

re: fclean all

.PHONY: all clean fclean re mlx