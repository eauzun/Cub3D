/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:02:46 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:15:23 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Tek bir satırı map->width uzunluğunda pad'leyip pad_map[y]'e yazar. */
static int	padding_row(t_map *map, char **pad_map, int y)
{
	int	x;
	int	len;

	pad_map[y] = malloc(map->width + 1);
	if (!pad_map[y])
		return (-1);
	x = 0;
	len = ft_strlen(map->grid[y]);
	while (x < map->width)
	{
		if (x < len)
			pad_map[y][x] = map->grid[y][x];
		else
			pad_map[y][x] = ' ';
		x++;
	}
	pad_map[y][map->width] = '\0';
	return (0);
}

/* Tüm satır uzunluklarını aynı yapar; flood fill için gerekli. */
int	padding_map(t_map *map)
{
	char	**pad_map;
	int		y;

	pad_map = malloc(sizeof(char *) * (map->height + 1));
	if (!pad_map)
		return (-1);
	y = 0;
	while (y < map->height)
	{
		if (padding_row(map, pad_map, y) == -1)
		{
			free_grid(pad_map, y);
			return (-1);
		}
		y++;
	}
	pad_map[map->height] = NULL;
	free_grid(map->grid, map->height);
	map->grid = pad_map;
	return (0);
}

/* Tek hücreyi kontrol eder: N/S/E/W ise oyuncu bilgisini yazar, geçersiz karakter ise -1 döner. */
static int	validate_cell(t_map *map, int x, int y)
{
	char	c;

	c = map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_x = x;
		map->player_y = y;
		map->player_look = c;
		map->player_num++;
		map->grid[y][x] = '0';
		return (0);
	}
	if (c != '0' && c != '1' && c != ' ')
		return (-1);
	return (0);
}

/* Oyuncu sayısı ve konumunu bulur; 0, 1, ' ' dışı geçersiz karakter varsa -1 döner. */
static int	validate_player(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	map->player_num = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (validate_cell(map, x, y) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

/* Map'in kapalı olup olmadığını flood fill ile kontrol eder; dışarı sızıntı varsa -1 döner. */
static int	is_map_closed(t_map *map, t_game *game)
{
	int	open;

	open = 0;
	if (copy_grid(map, game) == -1)
		return (-1);
	flood_fill(map, map->player_x, map->player_y, &open);
	free_grid(map->copy_grid, map->height);
	map->copy_grid = NULL;
	return (open);
}
