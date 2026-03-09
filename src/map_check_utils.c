/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:15 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:14:07 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Dosya adının .cub ile bitip bitmediğini kontrol eder; geçerliyse 0, değilse -1 döner. */
int	check_file_extension(char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	if (len < 4)
		return (-1);
	if (file_path[len - 4] != '.'
		|| file_path[len - 3] != 'c'
		|| file_path[len - 2] != 'u'
		|| file_path[len - 1] != 'b')
		return (-1);
	return (0);
}

/* Flood fill için map grid'inin bir kopyasını oluşturup map->copy_grid'e yazar. */
int	copy_grid(t_map *map, t_game *game)
{
	int	i;

	i = 0;
	map->copy_grid = malloc(sizeof(char *) * map->height);
	if (!map->copy_grid)
		exit_check("malloc failed", 1, -1, game);
	while (i < map->height)
	{
		map->copy_grid[i] = ft_strdup(map->grid[i]);
		if (!map->copy_grid[i])
		{
			exit_check("string duplicate failed", 1, -1, game);
			return (-1);
		}
		i++;
	}
	return (0);
}

/* Recursive flood fill: (x,y)'den başlayarak ulaşılabilir hücreleri 'F' ile doldurur; dışarı çıkarsa open -1 olur. */
void	flood_fill(t_map *map, int x, int y, int *open)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
	{
		*open = -1;
		return ;
	}
	if (*open == -1)
		return ;
	if (map->copy_grid[y][x] == ' ' || map->copy_grid[y][x] == '\0')
	{
		*open = -1;
		return ;
	}
	if (map->copy_grid[y][x] == '1' || map->copy_grid[y][x] == 'F')
		return ;
	map->copy_grid[y][x] = 'F';
	flood_fill(map, x + 1, y, open);
	flood_fill(map, x, y + 1, open);
	flood_fill(map, x - 1, y, open);
	flood_fill(map, x, y - 1, open);
}

/* Tek bir '0' hücresinin komşularında boşluk olup olmadığını kontrol eder. */
static int	check_zero_neighbors(t_map *map, int x, int y)
{
	if (y - 1 < 0 || map->grid[y - 1][x] == ' ')
		return (-1);
	if (y + 1 >= map->height || map->grid[y + 1][x] == ' ')
		return (-1);
	if (x - 1 < 0 || map->grid[y][x - 1] == ' ')
		return (-1);
	if (x + 1 >= map->width || map->grid[y][x + 1] == ' ')
		return (-1);
	return (0);
}

/* Sıfırların yanında boşluk olup olmadığını kontrol eder. */
int	check_zero_boundaries(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' && check_zero_neighbors(map, x, y) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
