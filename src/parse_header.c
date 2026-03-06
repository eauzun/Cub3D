/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 01:13:01 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/06 17:21:05 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Verilen string içindeki virgül sayısını döndürür (renk parse için). */
static int	check_num_of_commas(char *str)
{
	int	i;
	int	num;

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

/* Texture path'inin .xpm uzantısıyla bitip bitmediğini kontrol eder; geçerliyse 0, değilse -1 döner. */
static int	check_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (-1);
	if (path[len - 4] != '.'
		|| path[len - 3] != 'x'
		|| path[len - 2] != 'p'
		|| path[len - 1] != 'm')
		return (-1);
	return (0);
}

/* Bir color parçasının yalnızca rakamlardan oluşup oluşmadığını kontrol eder; geçerliyse 0, değilse -1 döner. */
static int	is_valid_color_part(char *str)
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
static void	parse_color_parts(char **parts, int vals[3], t_game *game)
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

static void	parse_color_values(char *str, int vals[3], t_game *game)
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
static void	parse_color(char *str, t_color *color, t_game *game)
{
	int	vals[3];

	parse_color_values(str, vals, game);
	color->r = vals[0];
	color->g = vals[1];
	color->b = vals[2];
	color->is_set = 1;
}

/* Satırdaki tanımlayıcıdan (id_len karakter) sonraki değer kısmının başlangıç adresini döndürür. */
static char	*get_value(char *line, int id_len)
{
	char	*val;

	val = line + id_len;
	while (*val == ' ' || *val == '\t')
		val++;
	return (val);
}

/* NO/SO/WE/EA texture satırını parse edip config'e path yazar; tanınmazsa -1 döner. */
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
		parse_error(-1, game, "texture: duplicate identifier");
	val = get_value(line, 3);
	if (*val == '\0')
		parse_error(-1, game, "texture: path is empty");
	if (check_xpm_extension(val) == -1)
		parse_error(-1, game, "texture: must be a .xpm file");
	*target = ft_strdup(val);
	if (!*target)
		parse_error(-1, game, "texture: memory error");
	return (0);
}

/* Tek header satırını yorumlar: texture (NO/SO/WE/EA), F veya C ise parse eder; map satırıysa -1 döner. */
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