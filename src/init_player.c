/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:03:13 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/01 23:21:12 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "mlx_functions/render.h"

void	init_player(t_render *render)
{
	t_map	*map;

	map = render->map;
	render->player.x = map->player_x + 0.5;
	render->player.y = map->player_y + 0.5;
	if (map->player_look == 'N')
	{
		render->player.dir_x = 0;
		render->player.dir_y = -1;
		render->player.plane_x = 0.66;
		render->player.plane_y = 0;
	}
	else if (map->player_look == 'S')
	{
		render->player.dir_x = 0;
		render->player.dir_y = 1;
		render->player.plane_x = -0.66;
		render->player.plane_y = 0;
	}
	else if (map->player_look == 'E')
	{
		render->player.dir_x = 1;
		render->player.dir_y = 0;
		render->player.plane_x = 0;
		render->player.plane_y = 0.66;
	}
	else if (map->player_look == 'W')
	{
		render->player.dir_x = -1;
		render->player.dir_y = 0;
		render->player.plane_x = 0;
		render->player.plane_y = -0.66;
	}
}