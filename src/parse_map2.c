/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:22:13 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/06 15:36:28 by emuzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Satırın texture veya renk identifier ile başlayıp başlamadığını kontrol eder; başlıyorsa 1 döner. */
static int	is_header_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	return (0);
}

/* Map bittikten sonra kalan satırları okur; texture/color identifier gelirse hata ile çıkar. */
void	check_after_map(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		game->current_line = line;
		remove_newline(line);
		if (!is_empty_line(line) && is_header_identifier(line))
		{
			game->current_line = NULL;
			free(line);
			close(fd);
			get_next_line(-1);
			exit_check("content after map is invalid", 1, -1, game);
		}
		free(line);
		game->current_line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
}

/* Yeni satırı map grid'ine ekler; gerekirse grid kapasitesini ikiye katlar. */
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

/* Map'teki en uzun satırın karakter sayısını (genişlik) döndürür. */
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
