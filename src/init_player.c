/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:38:01 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:38:43 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "mlx_functions/render.h"

static void	init_player_n(t_render *render)
{
	render->player.dir_x = 0;
	render->player.dir_y = -1;
	render->player.plane_x = 0.66;
	render->player.plane_y = 0;
}

static void	init_player_s(t_render *render)
{
	render->player.dir_x = 0;
	render->player.dir_y = 1;
	render->player.plane_x = -0.66;
	render->player.plane_y = 0;
}

static void	init_player_e(t_render *render)
{
	render->player.dir_x = 1;
	render->player.dir_y = 0;
	render->player.plane_x = 0;
	render->player.plane_y = 0.66;
}

static void	init_player_w(t_render *render)
{
	render->player.dir_x = -1;
	render->player.dir_y = 0;
	render->player.plane_x = 0;
	render->player.plane_y = -0.66;
}

/* Map'teki oyuncu konum ve bakış yönüne göre render->player koordinat,
	dir ve plane değerlerini ayarlar. */
void	init_player(t_render *render)
{
	t_map	*map;

	map = render->map;
	render->player.x = map->player_x + 0.5;
	render->player.y = map->player_y + 0.5;
	if (map->player_look == 'N')
		init_player_n(render);
	else if (map->player_look == 'S')
		init_player_s(render);
	else if (map->player_look == 'E')
		init_player_e(render);
	else if (map->player_look == 'W')
		init_player_w(render);
}
