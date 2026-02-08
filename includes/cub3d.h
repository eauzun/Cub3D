/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merged                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 00:00:00 by merged            #+#    #+#             */
/*   Updated: 2026/02/08 00:00:00 by merged           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "get_next_line.h"
# include "libft.h"

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

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	int		tex_count;
	int		color_count;
}	t_tex;

typedef struct s_game
{
	t_map	map;
	t_tex	tex;
}	t_game;

int		error_msg(char *msg);
void	exit_game(t_game *game, char *msg, int status);
int		map_parse(char *file_path, t_map *map);
int		parse_config(int fd, t_tex *tex);
int		check_file_extension(char *file_path);
int		check_cubfile_syntax(int fd);
int		analyze_parse_line(char *line, t_tex *tex);
int		parse_floor(char *line, t_tex *tex);
int		parse_ceiling(char *line, t_tex *tex);
int		validate_map(t_map *map);
int		copy_grid(t_map *map);
int		check_zero_boundaries(t_map *map);
void	flood_fill(t_map *map, int x, int y, int *open);
void	free_map(t_map *map);
void	free_tex(t_tex *tex);
void	free_grid(char **map, int height);
void	free_game(t_game *game);
void	free_split(char **split);
char	*bypass_spaces(char *line);
int		check_after_map(int fd);
int		check_and_parse_line(char *line, t_tex *tex);

#endif