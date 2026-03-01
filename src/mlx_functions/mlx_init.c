/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:59:23 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/02 01:15:24 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "render.h"
#include <sys/time.h>

/* ─── forward declaration ─────────────────────────────────────────────────── */

static int	on_close(t_render *render);

/* ─── movement helpers ────────────────────────────────────────────────────── */

static char	get_cell(t_map *map, double x, double y)
{
	int	ix;
	int	iy;

	ix = (int)x;
	iy = (int)y;
	if (iy < 0 || iy >= map->height || ix < 0 || ix >= map->width)
		return (' ');
	if (ix >= (int)ft_strlen(map->grid[iy]))
		return (' ');
	return (map->grid[iy][ix]);
}

static void	try_move(t_render *render, double nx, double ny)
{
	if (get_cell(render->map, nx, render->player.y) != '1'
		&& get_cell(render->map, nx, render->player.y) != ' '
		&& get_cell(render->map, nx, render->player.y) != '\0')
		render->player.x = nx;
	if (get_cell(render->map, render->player.x, ny) != '1'
		&& get_cell(render->map, render->player.x, ny) != ' '
		&& get_cell(render->map, render->player.x, ny) != '\0')
		render->player.y = ny;
}

/* ─── rotation ────────────────────────────────────────────────────────────── */

static void	rotate_player(t_render *render, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	old_dir_x = render->player.dir_x;
	render->player.dir_x = render->player.dir_x * c - render->player.dir_y * s;
	render->player.dir_y = old_dir_x * s + render->player.dir_y * c;
	old_plane_x = render->player.plane_x;
	render->player.plane_x = render->player.plane_x * c
		- render->player.plane_y * s;
	render->player.plane_y = old_plane_x * s + render->player.plane_y * c;
}

/* ─── key hooks ───────────────────────────────────────────────────────────── */

static int	key_press(int key, t_render *render)
{
	if (key == KEY_ESC)
		on_close(render);
	if (key == KEY_W)
		render->key_w = 1;
	else if (key == KEY_S)
		render->key_s = 1;
	else if (key == KEY_A)
		render->key_a = 1;
	else if (key == KEY_D)
		render->key_d = 1;
	else if (key == KEY_LEFT)
		render->key_left = 1;
	else if (key == KEY_RIGHT)
		render->key_right = 1;
	return (0);
}

static int	key_release(int key, t_render *render)
{
	if (key == KEY_W)
		render->key_w = 0;
	else if (key == KEY_S)
		render->key_s = 0;
	else if (key == KEY_A)
		render->key_a = 0;
	else if (key == KEY_D)
		render->key_d = 0;
	else if (key == KEY_LEFT)
		render->key_left = 0;
	else if (key == KEY_RIGHT)
		render->key_right = 0;
	return (0);
}

/* ─── window / close ──────────────────────────────────────────────────────── */

static int	on_close(t_render *render)
{
	t_game	*game;

	game = render->game;
	free_render(render);
	free_game(game);
	exit(0);
	return (0);
}

int	init_mlx_window(t_render *render)
{
	render->mlx = mlx_init();
	if (!render->mlx)
		return (exit_check("MLX initialization failed", 1, 1, NULL));
	render->window = mlx_new_window(render->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!render->window)
	{
		mlx_destroy_display(render->mlx);
		free(render->mlx);
		render->mlx = NULL;
		return (exit_check("MLX window creation failed", 1, 1, NULL));
	}
	return (1);
}

/* ─── game loop ───────────────────────────────────────────────────────────── */

#define MOVE_SPEED_PER_SEC 2.0
#define ROT_SPEED_PER_SEC  2.0

static double	get_time_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static int	game_loop(t_render *render)
{
	double	now;
	double	dt;
	double	ms;
	double	ra;

	now = get_time_sec();
	dt = now - render->last_frame_time;
	render->last_frame_time = now;
	if (dt <= 0.0 || dt > 0.1)
		dt = 0.016;
	ms = MOVE_SPEED_PER_SEC * dt;
	ra = ROT_SPEED_PER_SEC * dt;
	if (render->key_w)
		try_move(render,
			render->player.x + render->player.dir_x * ms,
			render->player.y + render->player.dir_y * ms);
	if (render->key_s)
		try_move(render,
			render->player.x - render->player.dir_x * ms,
			render->player.y - render->player.dir_y * ms);
	if (render->key_a)
		try_move(render,
			render->player.x - render->player.plane_x * ms,
			render->player.y - render->player.plane_y * ms);
	if (render->key_d)
		try_move(render,
			render->player.x + render->player.plane_x * ms,
			render->player.y + render->player.plane_y * ms);
	if (render->key_left)
		rotate_player(render, -ra);
	if (render->key_right)
		rotate_player(render, ra);
	render_frame(render);
	return (0);
}

/* ─── pixel helper ────────────────────────────────────────────────────────── */

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

/* ─── ray helpers ─────────────────────────────────────────────────────────── */

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
	ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30
		: fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30
		: fabs(1 / ray->ray_dir_y);
	ray->step_x = (ray->ray_dir_x < 0) ? -1 : 1;
	ray->step_y = (ray->ray_dir_y < 0) ? -1 : 1;
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

/* ─── render frame ────────────────────────────────────────────────────────── */

static void	draw_ceiling_floor(t_render *render, int x, int ds, int de)
{
	int	y;
	int	ceiling_rgb;
	int	floor_rgb;

	ceiling_rgb = (render->config->ceiling.r << 16)
		| (render->config->ceiling.g << 8)
		| render->config->ceiling.b;
	floor_rgb = (render->config->floor.r << 16)
		| (render->config->floor.g << 8)
		| render->config->floor.b;
	y = 0;
	while (y < ds)
		put_pixel_to_mem(&render->frame, x, y++, ceiling_rgb);
	y = de + 1;
	while (y < render->frame.height)
		put_pixel_to_mem(&render->frame, x, y++, floor_rgb);
}

static void	draw_wall_column(t_render *render, t_ray_dir *ray,
		int x, double perp_dist)
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	t_image			*tex;
	int				y;
	unsigned int	color;

	line_height = (int)(render->frame.height / perp_dist);
	draw_start = (-line_height / 2 + render->frame.height / 2);
	draw_end = (line_height / 2 + render->frame.height / 2);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= render->frame.height)
		draw_end = render->frame.height - 1;
	if (ray->side == 0)
		tex_num = (ray->ray_dir_x > 0) ? 2 : 3;
	else
		tex_num = (ray->ray_dir_y > 0) ? 0 : 1;
	if (ray->side == 0)
		wall_x = render->player.y + perp_dist * ray->ray_dir_y;
	else
		wall_x = render->player.x + perp_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex = &render->images[tex_num];
	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / line_height;
	tex_pos = (draw_start - render->frame.height / 2.0
			+ line_height / 2.0) * step;
	draw_ceiling_floor(render, x, draw_start, draw_end);
	y = draw_start;
	while (y <= draw_end)
	{
		color = *(unsigned int *)(tex->mlx_addr
				+ ((int)tex_pos & (tex->height - 1)) * tex->mlx_line_length
				+ tex_x * (tex->mlx_bits_per_pixel / 8));
		tex_pos += step;
		put_pixel_to_mem(&render->frame, x, y, color);
		y++;
	}
}

int	render_frame(t_render *render)
{
	int			x;
	t_ray_dir	ray;
	double		perp_dist;

	if (!render->frame.mlx_addr)
		return (0);
	x = 0;
	while (x < render->frame.width)
	{
		init_ray_direction(&ray, render, x);
		calculate_delta_and_step(&ray);
		calculate_side_distance(&ray, render);
		dda_algorithm(&ray, render);
		perp_dist = calculate_wall_distance(&ray, render);
		if (perp_dist <= 0)
			perp_dist = 1e-6;
		draw_wall_column(render, &ray, x, perp_dist);
		x++;
	}
	mlx_put_image_to_window(render->mlx, render->window,
		render->frame.mlx_img, 0, 0);
	return (1);
}

/* ─── texture loader ──────────────────────────────────────────────────────── */

static void	load_textures(t_render *render)
{
	char	*paths[4];
	int		w;
	int		h;
	int		i;

	paths[0] = render->config->no;
	paths[1] = render->config->so;
	paths[2] = render->config->we;
	paths[3] = render->config->ea;
	i = 0;
	while (i < 4)
	{
		if (!paths[i])
		{
			free_render(render);
			free_game(render->game);
			exit_check("texture: missing path", 1, -1, NULL);
		}
		render->images[i].mlx_img = mlx_xpm_file_to_image(render->mlx,
				paths[i], &w, &h);
		if (!render->images[i].mlx_img)
		{
			free_render(render);
			free_game(render->game);
			exit_check("texture: failed to load XPM", 1, -1, NULL);
		}
		render->images[i].mlx_addr = mlx_get_data_addr(
				render->images[i].mlx_img,
				&render->images[i].mlx_bits_per_pixel,
				&render->images[i].mlx_line_length,
				&render->images[i].mlx_endian);
		render->images[i].width = w;
		render->images[i].height = h;
		i++;
	}
}

/* ─── init render ─────────────────────────────────────────────────────────── */

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