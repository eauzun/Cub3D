/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:12:26 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/08 19:21:35 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

int	check_file_extension(char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	if (len < 4)
		return (-1);
	if (file_path[len - 4] != '.'
		|| file_path[len - 3] != 'c'
		|| file_path[len - 2] != 'u'
		|| file_path[len - 1] != 'b')
		return (-1);
	return (0);
}

int	copy_grid(t_map *map)
{
	int	i;

	i = 0;
	map->copy_grid = malloc(sizeof(char *) * map->height);
	if (!map->copy_grid)
		return (error_msg("malloc error"));
	while (i < map->height)
	{
		map->copy_grid[i] = ft_strdup(map->grid[i]);
		if (!map->copy_grid[i])
		{
			free_grid(map->copy_grid, i);
			map->copy_grid = NULL;
			return (error_msg("strdup error"));
		}
		i++;
	}
	return (0);
}

void	flood_fill(t_map *map, int x, int y, int *open)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
	{
		*open = -1;
		return ;
	}
	if (*open == -1)
		return ;
	if (map->copy_grid[y][x] == ' ' || map->copy_grid[y][x] == '\0')
	{
		*open = -1;
		return ;
	}
	if (map->copy_grid[y][x] == '1' || map->copy_grid[y][x] == 'F')
		return ;
	map->copy_grid[y][x] = 'F';
	flood_fill(map, x + 1, y, open);
	flood_fill(map, x, y + 1, open);
	flood_fill(map, x - 1, y, open);
	flood_fill(map, x, y - 1, open);
}

int	check_zero_boundaries(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0')
			{
				if (y - 1 < 0 || map->grid[y - 1][x] == ' ')
					return (-1);
				if (y + 1 >= map->height || map->grid[y + 1][x] == ' ')
					return (-1);
				if (x - 1 < 0 || map->grid[y][x - 1] == ' ')
					return (-1);
				if (x + 1 >= map->width || map->grid[y][x + 1] == ' ')
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

char	*bypass_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}
