/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:39:04 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_config(t_config *config)
{
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor.is_set = 0;
	config->ceiling.is_set = 0;
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_render	render;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&render, sizeof(t_render));
	init_config(&game.config);
	game.current_line = NULL;
	if (argc != 2)
	{
		write(2, "Usage: ./cub3d <map_file>\n", 25);
		return (1);
	}
	map_parse(argv[1], &game);
	render.map = &game.map;
	render.config = &game.config;
	render.game = &game;
	init_player(&render);
	init_render(&render);
	mlx_loop(render.mlx);
	return (0);
}
