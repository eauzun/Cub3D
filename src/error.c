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

/*
** exit_check:
**   msg    - yazılacak mesaj (NULL olabilir)
**   err    - 1 ise stderr'e "Error\n" prefix'i eklenir
**   status - (-1) ise free_game yapıp exit(1) çağırır
**            (0)  ise sadece 0 döner
**            diğer değerlerde o değeri döner
**   game   - free edilecek yapı (NULL geçilebilir)
*/
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