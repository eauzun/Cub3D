/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:38:41 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/08 19:21:31 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_config_line(char *line)
{
	line = bypass_spaces(line);
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

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

static int	check_line(char *line)
{
	if (is_empty_line(line))
		return (0);
	if (is_config_line(line))
		return (-1);
	return (0);
}

int	check_cubfile_syntax(int fd)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = check_line(line);
		free(line);
		if (ret == -1)
			return (error_msg("Invalid .cub file syntax"));
	}
	return (0);
}

int	check_after_map(int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			{
				free(line);
				return (error_msg("Content after map is not allowed"));
			}
			i++;
		}
		free(line);
	}
	return (0);
}