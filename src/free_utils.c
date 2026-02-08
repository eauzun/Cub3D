/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:12 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/08 19:21:33 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y])
			free(map->grid[y]);
		y++;
	}
	free(map->grid);
	if (map->copy_grid)
		free_grid(map->copy_grid, map->height);
	map->grid = NULL;
	map->copy_grid = NULL;
	map->height = 0;
	map->width = 0;
}

void	free_grid(char **map, int height)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void	free_tex(t_tex *tex)
{
	if (!tex)
		return ;
	if (tex->no)
		free(tex->no);
	if (tex->so)
		free(tex->so);
	if (tex->we)
		free(tex->we);
	if (tex->ea)
		free(tex->ea);
	tex->no = NULL;
	tex->so = NULL;
	tex->we = NULL;
	tex->ea = NULL;
	tex->f_r = -1;
	tex->f_g = -1;
	tex->f_b = -1;
	tex->c_r = -1;
	tex->c_g = -1;
	tex->c_b = -1;
	tex->tex_count = 0;
	tex->color_count = 0;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_tex(&game->tex);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}