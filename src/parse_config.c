/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:32:53 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/08 19:23:02 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_empty_line(char *line)
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

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	tex_init(t_tex *tex)
{
	tex->no = NULL;
	tex->so = NULL;
	tex->we = NULL;
	tex->ea = NULL;
	tex->f_r = -1;
	tex->f_g = -1;
	tex->f_b = -1;
	tex->c_r = -1;
	tex->c_g = -1;
	tex->c_b = -1;
	tex->tex_count = 0;
	tex->color_count = 0;
}

static int	process_line(char *line, t_tex *tex, int *map_started)
{
	if (is_empty_line(line))
		return (0);
	if (is_map_line(line))
	{
		*map_started = 1;
		return (1);
	}
	if (check_and_parse_line(line, tex) == -1)
		return (-1);
	return (0);
}

int	parse_config(int fd, t_tex *tex)
{
	char	*line;
	int		map_started;
	int		ret;

	map_started = 0;
	tex_init(tex);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = process_line(line, tex, &map_started);
		free(line);
		if (ret == -1)
			return (-1);
		if (ret == 1)
			break ;
	}
	if (check_after_map(fd) == -1)
		return (-1);
	if (tex->tex_count != 4 || tex->color_count != 2)
		return (error_msg("Missing texture or color definitions"));
	return (0);
}
