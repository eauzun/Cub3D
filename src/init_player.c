/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:03:13 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/06 16:33:38 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "mlx_functions/render.h"

static void init_player_N(t_render *render)
{
	render->player.dir_x = 0;
	render->player.dir_y = -1;
	render->player.plane_x = 0.66;
	render->player.plane_y = 0;
}

static void init_player_S(t_render *render)
{
	render->player.dir_x = 0;
	render->player.dir_y = 1;
	render->player.plane_x = -0.66;
	render->player.plane_y = 0;
}

static void init_player_E(t_render *render)
{
	render->player.dir_x = 1;
	render->player.dir_y = 0;
	render->player.plane_x = 0;
	render->player.plane_y = 0.66;
}

static void init_player_W(t_render *render)
{
	render->player.dir_x = -1;
	render->player.dir_y = 0;
	render->player.plane_x = 0;
	render->player.plane_y = -0.66;
}


/* Map'teki oyuncu konum ve bakış yönüne göre render->player koordinat, dir ve plane değerlerini ayarlar. */
void	init_player(t_render *render)
{
	t_map	*map;

	map = render->map;
	render->player.x = map->player_x + 0.5;
	render->player.y = map->player_y + 0.5;
	if (map->player_look == 'N')
		init_player_N(render);
	else if (map->player_look == 'S')
		init_player_S(render);
	else if (map->player_look == 'E')
		init_player_E(render);
	else if (map->player_look == 'W')
		init_player_W(render);	
}
