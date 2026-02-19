/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/19 04:14:43 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//return -1 olan her yerde geçmişteki şeyleri freelemeyi unutma!mak

int	main(int argc, char **argv)
{
	t_game	game;
	int		y;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3d <map_file>\n", 25);
		return (1);
	}
	game = (t_game){0};
	if (map_parse(argv[1], &game) == -1)
	{
		write(2, "Failed to parse map\n", 20);
		return (1);
	}
	y = 0;
	while (y < game.map.height)
	{
		write(1, game.map.grid[y], ft_strlen(game.map.grid[y]));
		write(1, "\n", 1);
		y++;
	}
	free_game(&game);
	return (0);
}

