/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:17 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:42:13 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	process_header_line(int fd, t_game *game, char *line,
		char **first_map_line)
{
	if (parse_header_line(line, game) == -1)
	{
		validate_headers(fd, game);
		game->current_line = NULL;
		*first_map_line = line;
		return (1);
	}
	free(line);
	game->current_line = NULL;
	return (0);
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
		if (process_header_line(fd, game, line, first_map_line))
			return ;
		line = get_next_line(fd);
	}
	validate_headers(fd, game);
}

static int	read_one_map_line(int fd, t_game *game, char *line, int *cap)
{
	game->current_line = line;
	remove_newline(line);
	if (is_empty_line(line))
	{
		free(line);
		game->current_line = NULL;
		check_after_map(fd, game);
		return (0);
	}
	game->current_line = NULL;
	append_line(&game->map, line, cap, game);
	return (1);
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
		if (!read_one_map_line(fd, game, line, &cap))
			return ;
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
