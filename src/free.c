/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:35 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:37:45 by ecakdemi         ###   ########.fr       */
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
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
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

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	if (game->map.copy_grid)
	{
		free_grid(game->map.copy_grid, game->map.height);
		game->map.copy_grid = NULL;
	}
	free_map(&game->map);
	free_config(&game->config);
}

void	free_render(t_render *render)
{
	if (!render)
		return ;
	free_texture_images(render);
	free_frame_and_window(render);
}
