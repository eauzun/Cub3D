/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:19:09 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/08 19:21:37 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	validate_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (1);
}

static int	parse_rgb(char *line, int *r, int *g, int *b)
{
	char	**split;
	int		ret;

	split = ft_split(line, ',');
	if (!split)
		return (-1);
	if (count_split(split) != 3)
	{
		free_split(split);
		return (-1);
	}
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_split(split);
	ret = validate_rgb(*r, *g, *b);
	return (ret);
}

int	parse_floor(char *line, t_tex *tex)
{
	char	*trim;
	int		ret;

	if (tex->f_r != -1 || tex->f_g != -1 || tex->f_b != -1)
		return (-1);
	trim = bypass_spaces(line + 1);
	ret = parse_rgb(trim, &tex->f_r, &tex->f_g, &tex->f_b);
	if (ret == 1)
		tex->color_count++;
	return (ret);
}

int	parse_ceiling(char *line, t_tex *tex)
{
	char	*trim;
	int		ret;

	if (tex->c_r != -1 || tex->c_g != -1 || tex->c_b != -1)
		return (-1);
	trim = bypass_spaces(line + 1);
	ret = parse_rgb(trim, &tex->c_r, &tex->c_g, &tex->c_b);
	if (ret == 1)
		tex->color_count++;
	return (ret);
}
