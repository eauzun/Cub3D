/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:35:08 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:35:53 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		i++;
	}
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
