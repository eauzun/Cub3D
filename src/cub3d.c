/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/08 19:21:29 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Usage: ./cub3d <map_file>\n", 27);
		return (1);
	}
	if (map_parse(argv[1], &game.map) == -1)
		exit_game(&game, "Failed to parse map", 1);
	free_game(&game);
	return (0);
}