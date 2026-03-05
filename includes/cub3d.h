#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "../src/mlx_functions/render.h"

/* -----------------------------------------------------------------------------
 *  Type definitions
 * --------------------------------------------------------------------------- */

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
	char		*current_line;
}	t_game;

typedef struct s_ray_dir
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray_dir;

/* -----------------------------------------------------------------------------
 *  Parse (map file, header, extension)
 * --------------------------------------------------------------------------- */

int		map_parse(char *file_path, t_game *game);
int		check_file_extension(char *file_path);
int		is_empty_line(char *line);
int		parse_header_line(char *line, t_game *game);

/* -----------------------------------------------------------------------------
 *  Map (grid, flood fill, validation, dimensions)
 * --------------------------------------------------------------------------- */

int		copy_grid(t_map *map, t_game *game);
int		validate_map(t_map *map, t_game *game);
int		check_zero_boundaries(t_map *map);
int		find_max_width(t_map *map);
void	append_line(t_map *map, char *line, int *cap, t_game *game);
void	flood_fill(t_map *map, int x, int y, int *open);
void	remove_newline(char *line);
void	check_after_map(int fd, t_game *game);

/* -----------------------------------------------------------------------------
 *  Free
 * --------------------------------------------------------------------------- */

void	free_map(t_map *map);
void	free_grid(char **map, int height);
void	free_config(t_config *config);
void	free_game(t_game *game);
void	free_render(t_render *render);

/* -----------------------------------------------------------------------------
 *  Error / exit
 * --------------------------------------------------------------------------- */

int		exit_check(char *msg, int err, int status, t_game *game);
void	parse_error(int fd, t_game *game, char *msg);

/* -----------------------------------------------------------------------------
 *  Player / game init
 * --------------------------------------------------------------------------- */

void	init_player(t_render *render);

#endif