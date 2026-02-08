/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:17 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/08 19:21:38 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	remove_newline(char *line)
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

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static int	find_max_width(t_map *map)
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

static int	read_map_lines(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		map->grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	map->width = find_max_width(map);
	if (validate_map(map) == -1)
		return (-1);
	return (0);
}

int	map_parse(char *file_path, t_map *map)
{
	int	fd;

	if (check_file_extension(file_path) == -1)
		return (error_msg("Invalid file extension"));
	map->height = count_lines(file_path);
	if (map->height <= 0)
		return (error_msg("Invalid map file"));
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (error_msg("malloc error"));
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		free(map->grid);
		return (error_msg("Cannot open file"));
	}
	if (read_map_lines(fd, map) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
