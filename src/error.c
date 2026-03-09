/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:36:34 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_check(char *msg, int err, int status, t_game *game)
{
	if (!msg && !err && !status)
		return (0);
	if (err)
		ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putendl_fd(msg, 1);
	if (status == -1)
	{
		get_next_line(-1);
		free_game(game);
		exit(1);
	}
	return (status);
}

void	parse_error(int fd, t_game *game, char *msg)
{
	if (fd >= 0)
		close(fd);
	get_next_line(-1);
	if (game && game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	exit_check(msg, 1, -1, game);
}

static void	validate_headers(int fd, t_game *game)
{
	if (!game->config.no || !game->config.so || !game->config.we
		|| !game->config.ea)
		parse_error(fd, game, "undefined texture identifier");
	if (!game->config.floor.is_set)
		parse_error(fd, game, "undefined floor color");
	if (!game->config.ceiling.is_set)
		parse_error(fd, game, "undefined ceiling color");
}
