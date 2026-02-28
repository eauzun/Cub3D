/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/28 02:18:14 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	init_config(t_config *config)
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
	t_game	game = {0};

	init_config(&game.config);
	if (argc != 2)
	{
		write(2, "Usage: ./cub3d <map_file>\n", 25);
		return (1);
	}
	t_render render = {0};

	// 1️⃣ Harita parse ediliyor
	map_parse(argv[1], &game);

	// 2️⃣ Render yapısına haritayı bağla  🔥 KRİTİK
	render.map = &game.map;
	render.config = &game.config;

	// 3️⃣ Player init (map pointer hazır)
	init_player(&render);
	fprintf(stderr, "MAIN: after init_player, player=(%.2f,%.2f) dir=(%.2f,%.2f)\n", 
		render.player.x, render.player.y, render.player.dir_x, render.player.dir_y);

	// 4️⃣ MLX + frame + ilk render tek fonksiyonla başlat (loop_hook init_render içinde)
	init_render(&render);

	mlx_loop(render.mlx);
	return (0);
}
