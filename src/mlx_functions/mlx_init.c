/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:59:23 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 15:41:59 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* ─── pixel helper ────────────────────────────────────────────────────────── */
/* Görsel belleğinde (x,y) konumuna verilen rengi yazar; sınır dışıysa hiçbir şey yapmaz. */
void	put_pixel_to_mem(t_image *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dest = img->mlx_addr
		+ (y * img->mlx_line_length + x * (img->mlx_bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

/* ─── frame init ──────────────────────────────────────────────────────────── */

/* Pencere boyutunda bir MLX görseli oluşturup render->frame alanlarına bağlar. */
int	init_frame(t_render *render)
{
	render->frame.mlx_img = mlx_new_image(render->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!render->frame.mlx_img)
		return (exit_check("MLX image creation failed", 1, 1, NULL));
	render->frame.mlx_addr = mlx_get_data_addr(render->frame.mlx_img,
			&render->frame.mlx_bits_per_pixel,
			&render->frame.mlx_line_length,
			&render->frame.mlx_endian);
	if (!render->frame.mlx_addr)
	{
		mlx_destroy_image(render->mlx, render->frame.mlx_img);
		render->frame.mlx_img = NULL;
		return (exit_check("MLX get data address failed", 1, 1, NULL));
	}
	render->frame.height = WINDOW_HEIGHT;
	render->frame.width = WINDOW_WIDTH;
	return (1);
}

/* ─── init render ─────────────────────────────────────────────────────────── */

/* Tuş bayraklarını, MLX penceresini, frame'i ve hook'ları ayarlar; texture'ları yükleyip ilk frame'i çizer. */
int	init_render(t_render *render)
{
	render->key_w = 0;
	render->key_s = 0;
	render->key_a = 0;
	render->key_d = 0;
	render->key_left = 0;
	render->key_right = 0;
	render->last_frame_time = 0.0;
	if (!init_mlx_window(render))
		return (0);
	if (!init_frame(render))
		return (0);
	mlx_hook(render->window, MLX_KEY_PRESS, 1L << 0, key_press, render);
	mlx_hook(render->window, MLX_KEY_RELEASE, 1L << 1, key_release, render);
	mlx_hook(render->window, MLX_DESTROY, 1L << 17, on_close, render);
	mlx_loop_hook(render->mlx, game_loop, render);
	if (render->config)
		load_textures(render);
	render_frame(render);
	return (1);
}
