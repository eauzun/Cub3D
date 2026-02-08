/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:25:49 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/08 19:21:39 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	trim_path(char *path)
{
	int	i;

	i = ft_strlen(path) - 1;
	while (i >= 0 && (path[i] == ' ' || path[i] == '\t' || path[i] == '\n'))
	{
		path[i] = '\0';
		i--;
	}
}

static char	*extract_path(char *line)
{
	char	*path;

	path = line + 2;
	while (*path == ' ' || *path == '\t')
		path++;
	return (path);
}

static int	parse_texture_path(char *line, char **tex_ptr, t_tex *tex)
{
	char	*path;

	if (*tex_ptr)
		return (-1);
	path = extract_path(line);
	trim_path(path);
	*tex_ptr = ft_strdup(path);
	if (!*tex_ptr)
		return (-1);
	tex->tex_count++;
	return (0);
}

static int	validate_texture(char *line, t_tex *tex)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_path(line, &tex->no, tex));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_path(line, &tex->so, tex));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_path(line, &tex->we, tex));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_path(line, &tex->ea, tex));
	return (-1);
}

int	check_and_parse_line(char *line, t_tex *tex)
{
	int	ret;

	line = bypass_spaces(line);
	ret = validate_texture(line, tex);
	if (ret != -1)
		return (ret);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_floor(line, tex));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_ceiling(line, tex));
	return (-1);
}