/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/19 01:45:02 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//1. argüman yazılacak mesaj (Mesaj yoksa null at null check zaten var)
//2. argüman error flag (varsa basına error yazdırıo)
//3. argüman exit status
int	exit_check(char *msg, int err, int status, t_game *game)
{
	int	fd;

	if (!msg && !err && !status)
		return (0);
	if (err)
		fd = 2;
	else
		fd = 1;
	if (err)
		ft_putstr_fd("Error\n", fd);
	if (msg)
		ft_putendl_fd(msg, fd);
	if (status == -1)
	{
		free_game(game);
		exit(1);
	}
	return (status);
}