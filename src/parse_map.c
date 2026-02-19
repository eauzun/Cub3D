/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:17 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/19 17:56:20 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
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

static void	read_headers(int fd, t_game *game, char **first_map_line)
{
	char	*line;

	*first_map_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parse_header_line(line, game) == -1)
		{
			check_headers_exist(game);
			*first_map_line = line;
			return ;
		}
		free(line);
		line = get_next_line(fd);
	}
	check_headers_exist(game);
}

static void	read_map_lines(int fd, t_game *game, char *first)
{
	char	*line;
	int		cap;

	cap = 16;
	game->map.grid = malloc(sizeof(char *) * cap);
	if (!game->map.grid)
		exit_check("memory allocation failed", 1, -1, game);
	game->map.height = 0;
	append_line(&game->map, first, &cap, game);
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			check_after_map(fd, game);
			return ;
		}
		append_line(&game->map, line, &cap, game);
		line = get_next_line(fd);
	}
	game->map.grid[game->map.height] = NULL;
}
int	map_parse(char *file_path, t_game *game)
{
	int		fd;
	char	*first;

	if (check_file_extension(file_path) == -1)
		exit_check("invalid file extension (expected .cub)", 1, -1, game);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_check("cannot open map file", 1, -1, game);
	read_headers(fd, game, &first);
	if (!first)
		exit_check("no map found in file", 1, -1, game);
	read_map_lines(fd, game, first);
	close(fd);
	if (game->map.height == 0)
		exit_check("map is empty", 1, -1, game);
	game->map.grid[game->map.height] = NULL;
	game->map.width = find_max_width(&game->map);
	validate_map(&game->map, game);
	return (0);
}


