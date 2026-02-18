/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:10 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/19 00:03:08 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int exit_check(char *msg, int err, int status, t_game *game)
{
	int fd;

	if(!msg && !err && !status)
		return(0);
	if(!err)
		fd = 1;
	if(err)
		ft_putstr_fd("Error: ", fd);
	if(msg)
		ft_putendl_fd(msg, fd);
	if(status == -1)
	{
		free_game(game);
		exit(status);
	}
	return(status);
}