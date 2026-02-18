/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:12 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/18 23:57:23 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

void free_grid(char **map, int height)
{
	int i;
	
	i = 0;
	if (!map)
		return;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

void free_exit(t_game *game)
{
	int fd;

	if(!game)
		return(0);
	if(game->map.copy_grid)
		free_grid(game->map.copy_grid, game-> map.height);
	if(&game->map)
		free_map(game->map);
}