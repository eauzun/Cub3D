/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:13:01 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/09 17:40:26 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*get_value(char *line, int id_len)
{
	char	*val;

	val = line + id_len;
	while (*val == ' ' || *val == '\t')
		val++;
	return (val);
}

int	parse_header_line(char *line, t_game *game)
{
	char	*val;

	if (parse_texture(line, game) == 0)
		return (0);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (game->config.floor.is_set)
			parse_error(-1, game, "color: duplicate floor color");
		val = get_value(line, 1);
		parse_color(val, &game->config.floor, game);
		return (0);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (game->config.ceiling.is_set)
			parse_error(-1, game, "color: duplicate ceiling color");
		val = get_value(line, 1);
		parse_color(val, &game->config.ceiling, game);
		return (0);
	}
	return (-1);
}
