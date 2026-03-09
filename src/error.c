/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:18:21 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Hata mesajı yazar; err=1 ise "Error\n" ekler; status=-1 ise free_game ile exit(1), aksi halde status döner. */
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

/* Parse hatası: fd'yi kapatır, GNL ve current_line'ı temizler, mesajla exit_check ile çıkar. */
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

/* Tüm texture ve zemin/tavan renklerinin tanımlı olup olmadığını kontrol eder; yoksa parse_error. */
static void	validate_headers(int fd, t_game *game)
{
	if (!game->config.no || !game->config.so
		|| !game->config.we || !game->config.ea)
		parse_error(fd, game, "undefined texture identifier");
	if (!game->config.floor.is_set)
		parse_error(fd, game, "undefined floor color");
	if (!game->config.ceiling.is_set)
		parse_error(fd, game, "undefined ceiling color");
}