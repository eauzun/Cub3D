#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	is_set;
}	t_color;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
}	t_config;

typedef struct s_map
{
	char	**grid;
	char	**copy_grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_look;
	int		player_num;
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_config	config;
}	t_game;

int		map_parse(char *file_path, t_game *game);
void	free_map(t_map *map);
int		check_file_extension(char *file_path);
int		copy_grid(t_map *map, t_game *game);
int		validate_map(t_map *map, t_game *game);
void	free_grid(char **map, int height);
void	free_config(t_config *config);
int		check_zero_boundaries(t_map *map);
void	flood_fill(t_map *map, int x, int y, int *open);
int		exit_check(char *msg, int err, int status, t_game *game);
void	free_game(t_game *game);
void	check_after_map(int fd, t_game *game);
void	append_line(t_map *map, char *line, int *cap, t_game *game);
int		find_max_width(t_map *map);
int		is_empty_line(char *line);
void	remove_newline(char *line);
int		parse_header_line(char *line, t_game *game);
void	check_headers_exist(t_game *game);

#endif