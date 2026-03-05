/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/02 01:26:02 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Hata mesajı yazar; err=1 ise "Error\n" ekler; status=-1 ise free_game ile exit(1), aksi halde status döner. */
int	exit_check(char *msg, int err, int status, t_game *game)
{
	int	fd;

	if (!msg && !err && !status)
		return (0);
	fd = err ? 2 : 1;
	if (err)
		ft_putstr_fd("Error\n", fd);
	if (msg)
		ft_putendl_fd(msg, fd);
	if (status == -1)
	{
		get_next_line(-1);
		free_game(game);
		exit(1);
	}
	return (status);
}