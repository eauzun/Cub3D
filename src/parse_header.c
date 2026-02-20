/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:13:01 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/20 22:39:15 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_headers_exist(t_game *game)
{
	if (!game->config.no || !game->config.so
		|| !game->config.we || !game->config.ea)
		exit_check("undefined texture identifier", 1, -1, game);
	if (!game->config.floor.is_set)
		exit_check("undefined floor color", 1, -1, game);
	if (!game->config.ceiling.is_set)
		exit_check("undefined ceiling color", 1, -1, game);
}

int check_num_of_commas(char *str) //virgül parse kontrol
{
	int i;
	int num;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			num++;
		i++;
	}
	return (num);
}

static void	parse_color(char *str, t_color *color, t_game *game)
{
	char	**parts;
	int		vals[3];
	int		i;

	if (check_num_of_commas(str) > 2) // virgül parse kontrolü
		exit_check("color: parse failed", 1, -1, game);
	parts = ft_split(str, ',');
	if (!parts)
		exit_check("color: parse failed", 1, -1, game);
	i = 0;
	while (i < 3)
	{
		if (!parts[i])
		{
			free_grid(parts, i);
			exit_check("color: missing value", 1, -1, game);
		}
		vals[i] = ft_atoi(parts[i]);
		if (vals[i] < 0 || vals[i] > 255)
		{
			free_grid(parts, 3);
			exit_check("color: incompatible value", 1, -1, game);
		}
		i++;
	}
	if (parts[3])
	{
		free_grid(parts, 4);
		exit_check("color: too many values", 1, -1, game);
	}
	color->r = vals[0];
	color->g = vals[1];
	color->b = vals[2];
	color->is_set = 1;
	free_grid(parts, 3);
}

static char	*get_value(char *line, int id_len)
{
	char	*val;

	val = line + id_len;
	while (*val == ' ' || *val == '\t')
		val++;
	return (val);
}

static int	parse_texture(char *line, t_game *game)
{
	char	**target;
	char	*val;

	target = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
		target = &game->config.no;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		target = &game->config.so;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		target = &game->config.we;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		target = &game->config.ea;
	else
		return (-1);
	if (*target)
		exit_check("texture: duplicate identifier", 1, -1, game);
	val = get_value(line, 3);
	if (*val == '\0')
		exit_check("texture: path is empty", 1, -1, game);
	*target = ft_strdup(val);
	if (!*target)
		exit_check("texture: memory error", 1, -1, game);
	return (0);
}

int	parse_header_line(char *line, t_game *game)
{
	char	*val;

	if (parse_texture(line, game) == 0)
		return (0);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (game->config.floor.is_set)
			exit_check("color: duplicate floor color", 1, -1, game);
		val = get_value(line, 1);
		parse_color(val, &game->config.floor, game);
		return (0);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (game->config.ceiling.is_set)
			exit_check("color: duplicate ceiling color", 1, -1, game);
		val = get_value(line, 1);
		parse_color(val, &game->config.ceiling, game);
		return (0);
	}
	return (-1);
}
