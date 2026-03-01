/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:17 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/01 00:00:00 by emuzun            ###   ########.fr       */
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

/*
** Tüm kaynakları temizleyip çıkış yapar.
** fd >= 0 ise kapatır. GNL static ve current_line temizlenir.
** exit_check zaten free_game çağırır; current_line önceden temizleniyor
** çünkü exit_check → free_game sırasına güvenmek yerine burada garantiliyoruz.
*/
void	parse_error(int fd, t_game *game, char *msg)
{
	if (fd >= 0)
		close(fd);
	get_next_line(-1);
	if (game && game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	exit_check(msg, 1, -1, game);
}

static void	validate_headers(int fd, t_game *game)
{
	if (!game->config.no || !game->config.so
		|| !game->config.we || !game->config.ea)
		parse_error(fd, game, "undefined texture identifier");
	if (!game->config.floor.is_set)
		parse_error(fd, game, "undefined floor color");
	if (!game->config.ceiling.is_set)
		parse_error(fd, game, "undefined ceiling color");
}

static void	read_headers(int fd, t_game *game, char **first_map_line)
{
	char	*line;

	*first_map_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		game->current_line = line;
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			game->current_line = NULL;
			line = get_next_line(fd);
			continue ;
		}
		if (parse_header_line(line, game) == -1)
		{
			validate_headers(fd, game);
			game->current_line = NULL;
			*first_map_line = line;
			return ;
		}
		free(line);
		game->current_line = NULL;
		line = get_next_line(fd);
	}
	validate_headers(fd, game);
}

static void	read_map_lines(int fd, t_game *game, char *first)
{
	char	*line;
	int		cap;

	cap = 16;
	game->map.grid = malloc(sizeof(char *) * cap);
	if (!game->map.grid)
		parse_error(fd, game, "memory allocation failed");
	game->map.height = 0;
	append_line(&game->map, first, &cap, game);
	line = get_next_line(fd);
	while (line)
	{
		game->current_line = line;
		remove_newline(line);
		if (is_empty_line(line))
		{
			free(line);
			game->current_line = NULL;
			check_after_map(fd, game);
			return ;
		}
		game->current_line = NULL;
		append_line(&game->map, line, &cap, game);
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
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
		parse_error(fd, game, "no map found in file");
	read_map_lines(fd, game, first);
	if (game->map.height == 0)
		exit_check("map is empty", 1, -1, game);
	game->map.grid[game->map.height] = NULL;
	game->map.width = find_max_width(&game->map);
	validate_map(&game->map, game);
	return (0);
}