/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/06 16:33:30 by emuzun           ###   ########.fr       */
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
