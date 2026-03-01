/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:12 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/01 00:00:00 by emuzun            ###   ########.fr       */
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

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->no)
	{
		free(config->no);
		config->no = NULL;
	}
	if (config->so)
	{
		free(config->so);
		config->so = NULL;
	}
	if (config->we)
	{
		free(config->we);
		config->we = NULL;
	}
	if (config->ea)
	{
		free(config->ea);
		config->ea = NULL;
	}
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
	int	i;

	if (!render)
		return ;
	i = 0;
	while (i < 4)
	{
		if (render->images[i].mlx_img)
		{
			mlx_destroy_image(render->mlx, render->images[i].mlx_img);
			render->images[i].mlx_img = NULL;
		}
		i++;
	}
	if (render->frame.mlx_img)
	{
		mlx_destroy_image(render->mlx, render->frame.mlx_img);
		render->frame.mlx_img = NULL;
	}
	if (render->window)
	{
		mlx_destroy_window(render->mlx, render->window);
		render->window = NULL;
	}
	if (render->mlx)
	{
		mlx_destroy_display(render->mlx);
		free(render->mlx);
		render->mlx = NULL;
	}
}