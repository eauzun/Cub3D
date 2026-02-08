CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
NAME = cub3d

SRC = src/cub3d.c src/parse_map.c src/map_parse_utils.c src/free_utils.c \
      external/get_next_line.c external/get_next_line_utils.c src/map_control_functions.c \
	  src/error.c

LIBS = external/libft/libft.a

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re