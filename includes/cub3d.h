#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

typedef struct s_map
{
	char	**grid;
	char	**copy_grid;
	int		width;
	int		height;
	int 	player_x;
	int		player_y;
	char	player_look;
	int		player_num;
}	t_map;

typedef struct s_game
{
	t_map	map;
}	t_game;

int		map_parse(char *file_path, t_map *map);
int		error_msg(char *msg);
void	free_map(t_map *map);
int     check_file_extension(char *file_path);
int     map_parse(char *file_path, t_map *map);
void    free_map(t_map *map);
int 	copy_grid(t_map *map);
int 	validate_map(t_map *map);
void	free_grid(char **map, int height);
int 	check_zero_boundaries(t_map *map);
void 	flood_fill(t_map *map, int x, int y, int *open);
int		exit_check(char *msg, int err, int status, t_game *game);
void	free_game(t_game *game);

#endif
