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
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	t_map	map;
}	t_game;

int	map_parse(char *file_path, t_map *map);
int		error_msg(char *msg);
void	free_map(t_map *map);
int     check_file_extension(char *file_path);
int     map_parse(char *file_path, t_map *map);
void    free_map(t_map *map);

#endif
