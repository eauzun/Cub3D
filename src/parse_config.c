/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:32:53 by emuzun            #+#    #+#             */
/*   Updated: 2026/02/18 23:40:30 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Satırın sadece boşluk/tab/newline içerip içermediğini kontrol eder; boşsa 1 döner. */
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

/* Satırın geçerli bir map satırı (0,1, boşluk, N/S/E/W, tab) olup olmadığını kontrol eder. */
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/* Texture ve renk sayacı dahil t_tex alanlarını varsayılan değerlere sıfırlar. */
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

/* Tek satırı işler: boşsa 0, map satırıysa 1, config satırıysa parse edip 0 döner; hata -1. */
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
		return (error_msg("Invalid config line"));
	return (0);
}

/* Dosyayı satır satır okuyup map satırı gelene veya dosya bitene kadar config satırlarını parse eder. */
static int	read_config_lines(int fd, t_tex *tex)
{
	char	*line;
	int		map_started;
	int		ret;

	map_started = 0;
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
	return (0);
}

/* Config dosyasını açar, texture ve renk tanımlarını parse eder; eksik tanım varsa -1 döner. */
int	parse_config(char *file_path, t_tex *tex)
{
	int	fd;

	tex_init(tex);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (error_msg("Cannot open file"));
	if (read_config_lines(fd, tex) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (tex->tex_count != 4 || tex->color_count != 2)
		return (error_msg("Missing texture or color definitions"));
	return (0);
}
