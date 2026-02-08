CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
NAME = cub3d
TEST_NAME = test_cub3d

SRC = src/cub3d.c \
      src/parse_map.c \
      src/map_parse_utils.c \
      src/map_control_functions.c \
      src/parse_config.c \
      src/parse_elements.c \
      src/parse_textures.c \
      src/cubfile_syntax.c \
      src/free_utils.c \
      src/error.c \
      external/get_next_line.c \
      external/get_next_line_utils.c

TEST_SRC = src/test_main.c \
           src/parse_map.c \
           src/map_parse_utils.c \
           src/map_control_functions.c \
           src/parse_config.c \
           src/parse_elements.c \
           src/parse_textures.c \
           src/cubfile_syntax.c \
           src/free_utils.c \
           src/error.c \
           external/get_next_line.c \
           external/get_next_line_utils.c

LIBS = external/libft.a

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(LIBS) $(INCLUDES) -o $(NAME)

test: $(TEST_NAME)

$(TEST_NAME):
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIBS) $(INCLUDES) -o $(TEST_NAME)
	@echo ""
	@echo "✅ Test program compiled!"
	@echo "Run with: ./test_cub3d etc/map.cub"
	@echo ""

clean:
	@rm -f $(NAME) $(TEST_NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re test