/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:16:00 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/09 14:16:10 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Bir color parçasının yalnızca rakamlardan oluşup oluşmadığını kontrol eder; geçerliyse 0, değilse -1 döner. */
int	is_valid_color_part(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

/* "R,G,B" stringini parçalayıp 0-255 arası değerleri vals dizisine yazar; hata durumunda parse_error ile çıkar. */
void	parse_color_parts(char **parts, int vals[3], t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!parts[i] || is_valid_color_part(parts[i]) == -1)
		{
			free_grid(parts, 3);
			parse_error(-1, game, "color: invalid value");
		}
		vals[i] = ft_atoi(parts[i]);
		if (vals[i] < 0 || vals[i] > 255)
		{
			free_grid(parts, 3);
			parse_error(-1, game, "color: incompatible value");
		}
		i++;
	}
}

void	parse_color_values(char *str, int vals[3], t_game *game)
{
	char	**parts;

	if (check_num_of_commas(str) > 2)
		parse_error(-1, game, "color: parse failed");
	parts = ft_split(str, ',');
	if (!parts)
		parse_error(-1, game, "color: parse failed");
	parse_color_parts(parts, vals, game);
	if (parts[3])
	{
		free_grid(parts, 4);
		parse_error(-1, game, "color: too many values");
	}
	free_grid(parts, 3);
}

/* Renk stringini parse edip t_color yapısına yazar ve is_set'i 1 yapar. */
void	parse_color(char *str, t_color *color, t_game *game)
{
	int	vals[3];

	parse_color_values(str, vals, game);
	color->r = vals[0];
	color->g = vals[1];
	color->b = vals[2];
	color->is_set = 1;
}
