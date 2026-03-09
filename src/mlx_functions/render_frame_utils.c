/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:40:28 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:45:23 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_wall_line(double perp_dist, t_render *render,
		t_wall_column *wall_column)
{
	wall_column->line_height = (int)(render->frame.height / perp_dist);
	wall_column->draw_start = -wall_column->line_height / 2
		+ render->frame.height / 2;
	wall_column->draw_end = wall_column->line_height / 2
		+ render->frame.height / 2;
	if (wall_column->draw_start < 0)
		wall_column->draw_start = 0;
	if (wall_column->draw_end >= render->frame.height)
		wall_column->draw_end = render->frame.height - 1;
}

void	select_texture_index(t_ray_dir *ray, t_wall_column *wall_column)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			wall_column->texture_index = 2;
		else
			wall_column->texture_index = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			wall_column->texture_index = 0;
		else
			wall_column->texture_index = 1;
	}
}

double	calculate_wall_x(t_render *render, t_ray_dir *ray,
		double perp_dist)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = render->player.y + perp_dist * ray->ray_dir_y;
	else
		wall_x = render->player.x + perp_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	init_texture_coords(t_render *render, t_ray_dir *ray,
		t_wall_column *wall_column)
{
	t_image	*texture;

	texture = &render->images[wall_column->texture_index];
	wall_column->texture_x = (int)(wall_column->wall_x
			* (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		wall_column->texture_x = texture->width - wall_column->texture_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		wall_column->texture_x = texture->width - wall_column->texture_x - 1;
	wall_column->step = 1.0 * texture->height / wall_column->line_height;
	wall_column->texture_position = (wall_column->draw_start
			- render->frame.height / 2.0
			+ wall_column->line_height / 2.0) * wall_column->step;
}
