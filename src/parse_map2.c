/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:22:13 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/19 03:31:04 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Map basladiktan sonra kalan satirlari okur.
** Bos olmayan herhangi bir satir gelirse "content after map" hatasiyla cikis yapar.
** Dosya burada biterse gecerlidir.
*/
void	check_after_map(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (!is_empty_line(line))
		{
			free(line);
			exit_check("content after map is invalid", 1, -1, game);
		}
		free(line);
		line = get_next_line(fd);
	}
}


void	append_line(t_map *map, char *line, int *cap, t_game *game)
{
	char	**tmp;

	if (map->height >= *cap - 1)
	{
		*cap *= 2;
		tmp = malloc(sizeof(char *) * *cap);
		if (!tmp)
			exit_check("memory allocation failed", 1, -1, game);
		ft_memcpy(tmp, map->grid, sizeof(char *) * map->height);
		free(map->grid);
		map->grid = tmp;
	}
	map->grid[map->height] = line;
	map->height++;
}

int	find_max_width(t_map *map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (i < map->height)
	{
		len = ft_strlen(map->grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

