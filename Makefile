CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

INCLUDES = -I includes -I src/mlx_functions -I $(MLX_DIR)

LIBFT = external/libft/libft.a

SRC = \
src/main.c \
src/parse_map.c \
src/map_parse_header.c \
src/map_parsing_utils.c \
src/map_parse_color.c \
src/map_check_utils.c \
src/check_after_map.c \
src/validate_map.c \
src/validate_map_utils.c \
src/init_player.c \
src/free.c \
src/free_utils.c \
src/error.c \
external/get_next_line.c \
external/get_next_line_utils.c \
src/mlx_functions/mlx_init.c \
src/mlx_functions/mlx_func.c \
src/mlx_functions/game_loop.c \
src/mlx_functions/render_frame.c \
src/mlx_functions/render_frame_utils.c \
src/mlx_functions/ray_and_dda_functions.c \
src/mlx_functions/rotate_player_and_cam.c \
src/mlx_functions/texture_loader.c

OBJ = $(SRC:.c=.o)

all: mlx $(LIBFT) $(NAME)

mlx:
	@make -C $(MLX_DIR) 2>/dev/null || true

$(LIBFT):
	@make -C external/libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJ)
	@make -C external/libft clean 2>/dev/null || true

fclean: clean
	rm -f $(NAME)
	@make -C external/libft fclean 2>/dev/null || true

re: fclean all

.PHONY: all clean fclean re mlx