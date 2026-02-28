/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:03:13 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/28 02:17:31 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "mlx_functions/render.h"
#include <stdio.h>

//bu fonksiyonu 4 e bölmeyi düşünüyorum.
void init_player(t_render *render) //player'ın konumunu ve yönünü başlatır, bu fonksiyon, render yapısındaki player'ı, harita verilerine göre doğru konuma ve yöne ayarlamak için kullanılır. Player'ın başlangıç konumu ve bakış yönü, harita dosyasındaki bilgilerle uyumlu olmalıdır.
{
	t_map *map = render->map;
	fprintf(stderr, "INIT_PLAYER: player_x=%d player_y=%d player_look='%c'\n", map->player_x, map->player_y, map->player_look);

	render->player.x = map->player_x + 0.5; // Player'ın tam ortasında başlatmak için 0.5 ekliyoruz (hücre ortası)
	render->player.y = map->player_y + 0.5;
	
	if (map->player_look == 'N')
	{
		render->player.dir_x = 0;
		render->player.dir_y = -1;
		render->player.plane_x = 0.66; // FOV'yi belirler, 0.66 genellikle kullanılır. 0.3 zoom gibi, 1 balık gözü gibi görür. (görüş açısı) sağ-sol yönünde hareket ederken kameranın görüş genişliğini belirler.
		render->player.plane_y = 0; //yukarı-aşağı yönünde hareket ederken kameranın görüş genişliğini belirler.
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


