/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_and_dda_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:31:12 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:44:54 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	init_ray_direction(t_ray_dir *ray, t_render *render, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)render->frame.width - 1;
	ray->ray_dir_x = render->player.dir_x
		+ render->player.plane_x * camera_x;
	ray->ray_dir_y = render->player.dir_y
		+ render->player.plane_y * camera_x;
	ray->map_x = (int)render->player.x;
	ray->map_y = (int)render->player.y;
	ray->hit = 0;
	return (0);
}

void	calculate_delta_and_step(t_ray_dir *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	calculate_side_distance(t_ray_dir *ray, t_render *render)
{
	if (ray->ray_dir_x < 0)
		ray->side_dist_x = (render->player.x - ray->map_x)
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - render->player.x)
			* ray->delta_dist_x;
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = (render->player.y - ray->map_y)
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - render->player.y)
			* ray->delta_dist_y;
}

void	dda_algorithm(t_ray_dir *ray, t_render *render)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= render->map->height
			|| ray->map_x < 0 || ray->map_x >= render->map->width)
		{
			ray->hit = 1;
			break ;
		}
		if (render->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

double	calculate_wall_distance(t_ray_dir *ray, t_render *render)
{
	if (ray->side == 0)
		return ((ray->map_x - render->player.x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x);
	return ((ray->map_y - render->player.y
			+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y);
}
