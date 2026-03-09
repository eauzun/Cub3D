/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:33:36 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 14:18:17 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* Tek kolonda tavan ve zemin bölümlerini config renklerine göre çizer. */
void	draw_ceiling_floor(t_render *render, int screen_x,
		int draw_start, int draw_end)
{
	int	pixel_y;
	int	ceiling_rgb;
	int	floor_rgb;

	ceiling_rgb = (render->config->ceiling.r << 16)
		| (render->config->ceiling.g << 8)
		| render->config->ceiling.b;
	floor_rgb = (render->config->floor.r << 16)
		| (render->config->floor.g << 8)
		| render->config->floor.b;
	pixel_y = 0;
	while (pixel_y < draw_start)
		put_pixel_to_mem(&render->frame, screen_x, pixel_y++, ceiling_rgb);
	pixel_y = draw_end + 1;
	while (pixel_y < render->frame.height)
		put_pixel_to_mem(&render->frame, screen_x, pixel_y++, floor_rgb);
}

/* Tek bir duvar kolonunu texture'tan örnekleyerek ekrana çizer. */
void	draw_textured_column(t_render *render, int screen_x,
		t_wall_column *wall_column)
{
	int				pixel_y;
	t_image			*texture;
	unsigned int	color;

	texture = &render->images[wall_column->texture_index];
	pixel_y = wall_column->draw_start;
	while (pixel_y <= wall_column->draw_end)
	{
		color = *(unsigned int *)(texture->mlx_addr
				+ ((int)wall_column->texture_position & (texture->height - 1))
				* texture->mlx_line_length
				+ wall_column->texture_x
				* (texture->mlx_bits_per_pixel / 8));
		wall_column->texture_position += wall_column->step;
		put_pixel_to_mem(&render->frame, screen_x, pixel_y, color);
		pixel_y++;
	}
}

/* Tek ekran kolonu için duvar çizimini koordine eder: boyut, texture seçimi, tavan/zemin ve texture kolonu. */
void	draw_wall_column(t_render *render, t_ray_dir *ray,
		int screen_x, double perp_dist)
{
	t_wall_column	wall_column;

	init_wall_line(perp_dist, render, &wall_column);
	select_texture_index(ray, &wall_column);
	wall_column.wall_x = calculate_wall_x(render, ray, perp_dist);
	init_texture_coords(render, ray, &wall_column);
	draw_ceiling_floor(render, screen_x,
		wall_column.draw_start, wall_column.draw_end);
	draw_textured_column(render, screen_x, &wall_column);
}

/* Tüm ekran kolonları için ışın atıp duvarları çizer ve görseli pencereye kopyalar. */
int	render_frame(t_render *render)
{
	int			screen_x;
	t_ray_dir	ray;
	double		perp_dist;
	/* perp_dist: oyuncudan duvara dik uzaklık; duvar yüksekliği buna göre hesaplanır. */
	if (!render->frame.mlx_addr)
		return (0);
	screen_x = 0;
	while (screen_x < render->frame.width)
	{
		init_ray_direction(&ray, render, screen_x);
		calculate_delta_and_step(&ray);
		calculate_side_distance(&ray, render);
		dda_algorithm(&ray, render);
		perp_dist = calculate_wall_distance(&ray, render);
		if (perp_dist <= 0)
			perp_dist = 1e-6;
		draw_wall_column(render, &ray, screen_x, perp_dist);
		screen_x++;
	}
	mlx_put_image_to_window(render->mlx, render->window,
		render->frame.mlx_img, 0, 0);
	return (1);
}
