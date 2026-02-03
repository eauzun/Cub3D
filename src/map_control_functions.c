/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:02:46 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/03 20:57:16 by ecakdemi         ###   ########.fr       */
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

void flood_fill(t_map *map, int x, int y, int *open) // dümdüz flood fill, F ile dolduracak gidebildiğim yerleri.
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
	{
		*open = -1;
		return;
	}
	if (*open == -1)
		return;
	if (map->copy_grid[y][x] == ' ' || map->copy_grid[y][x] == '\0')
	{
		*open = -1;
		return;
	}
	if (map->copy_grid[y][x] == '1' || map->copy_grid[y][x] == 'F')
		return;
	map->copy_grid[y][x] = 'F';
	flood_fill(map, x + 1, y, open);
	flood_fill(map, x, y + 1, open);
	flood_fill(map, x - 1, y, open);
	flood_fill(map, x, y - 1, open);
}

static int is_map_closed(t_map *map) // bu fonksiyon mapin kapalı olup olmadığını kontrol eder.
{
	int open;

	open = 0;
	if (copy_grid(map) == -1)
		return (-1);
	flood_fill(map, map->player_x, map->player_y, &open);
	free_grid(map->copy_grid, map->height); // bu fonk yazılacak.
	//map->copy_grid = NULL; // freelendikten sonra bunu aç.
	return (open);
}

int validate_map(t_map *map) // bu fonksiyon mapin doğru olup olmadığını kontrol eder.
{
	if (padding_map(map) == -1)
	{
		error_msg("map padding failed!");	
		return (-1);
	}
	if (validate_player(map) == -1)
	{
		error_msg("validate player error!");
		return (-1);
	}
	if (is_map_closed(map) == -1)
	{
		error_msg("map is not closed!");
		return (-1);
	}
	if (map->player_num != 1)
	{
		error_msg("player count error!");
		return (-1);
	}
	return (0);
}