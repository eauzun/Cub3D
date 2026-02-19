/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:02:46 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/19 03:57:41 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int padding_map(t_map *map) // bu fonksiyon bölünecek. tüm satır uzunluklarını aynı yapmak amaçlı, yoksa flood fill düzgün çalışmıyor.
{
	char **pad_map;
	int y;
	int x;
	int len;
	
	pad_map = malloc(sizeof(char *) * map->height);
	if (!pad_map)
		return (-1);
	y = 0;
	while (y < map->height)
	{
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
		y++;
	}
	free_grid(map->grid, map->height);
	map->grid = pad_map;
	return (0);
}

static int validate_player(t_map *map) // bu fonksiyon hem player sayı kontrolünü, hem player yerini bulur. 0 1 ve ' ' karakteri dışındakiler için kontrol yapar.  
{
	int x;
	int y;
	
	y = 0;
	map->player_num = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' || map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				map->player_x = x;
				map->player_y = y;
				map->player_num++;
				map->grid[y][x] = '0'; //oyuncu bulunduğu kareden yürüyebilmeli, o yüzden değiştiriyorum.
			}
			else if (map->grid[y][x] != '0' && map->grid[y][x] != '1' && map->grid[y][x] != ' ')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

static int is_map_closed(t_map *map, t_game *game) // bu fonksiyon mapin kapalı olup olmadığını kontrol eder.
{
	int open;

	open = 0;
	if (copy_grid(map, game) == -1)
		return (-1);
	flood_fill(map, map->player_x, map->player_y, &open);
	free_grid(map->copy_grid, map->height); // bu fonk yazılacak.
	map->copy_grid = NULL; // freelendikten sonra bunu aç.
	return (open);
}

int validate_map(t_map *map, t_game *game) // bu fonksiyon mapin doğru olup olmadığını kontrol eder.
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
//bu fonksiyonu düzenledim. -1 durumu için yazdığım fonksiyona entegre ettim.