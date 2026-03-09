/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:24:25 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:18:59 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Map doğrulaması: padding, oyuncu, sıfır sınırları ve kapalılık kontrolü; hata durumunda exit_check ile çıkar. */
int	validate_map(t_map *map, t_game *game)
{
	if (padding_map(map) == -1)
		exit_check("map padding failed", 1, -1, game);
	if (validate_player(map) == -1)
		exit_check("player validation failed", 1, -1, game);
	if (map->player_num != 1)
		exit_check("invalid player count", 1, -1, game);
	if (check_zero_boundaries(map) == -1)
		exit_check("zero num error!", 1, -1, game);
	if (is_map_closed(map, game) == -1)
		exit_check("map is not closed!", 1, -1, game);
	return (0);
}
