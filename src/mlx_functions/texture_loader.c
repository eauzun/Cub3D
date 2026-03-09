/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:32:35 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:16:36 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* ─── texture loader ──────────────────────────────────────────────────────── */

/* Texture dosya yollarını config'ten alıp diziye yerleştirir. */
static void	init_texture_paths(t_render *render, char *texture_paths[4])
{
	texture_paths[0] = render->config->no;
	texture_paths[1] = render->config->so;
	texture_paths[2] = render->config->we;
	texture_paths[3] = render->config->ea;
}

/* Bir texture yolu boşsa, kaynakları serbest bırakır ve hata ile çıkar. */
static void	validate_texture_path(t_render *render, char *texture_path)
{
	if (!texture_path)
	{
		free_render(render);
		free_game(render->game);
		exit_check("texture: missing path", 1, -1, NULL);
	}
}

/* Tek bir XPM texture dosyasını yükler ve ilgili t_image alanlarını doldurur. */
static void	load_single_texture(t_render *render, t_image *image,
		char *texture_path)
{
	int	texture_width;
	int	texture_height;

	image->mlx_img = mlx_xpm_file_to_image(render->mlx,
			texture_path, &texture_width, &texture_height);
	if (!image->mlx_img)
	{
		free_render(render);
		free_game(render->game);
		exit_check("texture: failed to load XPM", 1, -1, NULL);
	}
	image->mlx_addr = mlx_get_data_addr(
			image->mlx_img,
			&image->mlx_bits_per_pixel,
			&image->mlx_line_length,
			&image->mlx_endian);
	image->width = texture_width;
	image->height = texture_height;
}

/* Dört duvar texture'ını config path'lerinden yükleyip render->images dizisine yazar. */
static void	load_textures(t_render *render)
{
	char	*texture_paths[4];
	int		index;

	init_texture_paths(render, texture_paths);
	index = 0;
	while (index < 4)
	{
		validate_texture_path(render, texture_paths[index]);
		load_single_texture(render, &render->images[index],
			texture_paths[index]);
		index++;
	}
}
