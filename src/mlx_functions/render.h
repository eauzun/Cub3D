/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:30:52 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/09 15:41:58 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../mlx/mlx.h"
# include "../includes/cub3d.h"
# include <math.h>
# include <sys/time.h>

/* -----------------------------------------------------------------------------
 *  Forward declarations (types defined in cub3d.h)
 * --------------------------------------------------------------------------- */

typedef struct s_config		t_config;
typedef struct s_map		t_map;
typedef struct s_ray_dir	t_ray_dir;
typedef struct s_game		t_game;

/* -----------------------------------------------------------------------------
 *  Constants
 * --------------------------------------------------------------------------- */

# define WINDOW_WIDTH   800
# define WINDOW_HEIGHT  600

# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363

# define MLX_KEY_PRESS    2
# define MLX_KEY_RELEASE  3
# define MLX_DESTROY      17

# define MOVE_SPEED_PER_SEC  2.0
# define ROT_SPEED_PER_SEC   2.0

/* -----------------------------------------------------------------------------
 *  Type definitions (render / MLX)
 * --------------------------------------------------------------------------- */

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_image
{
	void	*mlx_img;
	char	*mlx_addr;
	int		mlx_bits_per_pixel;
	int		mlx_line_length;
	int		mlx_endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_render
{
	void		*mlx;
	void		*window;
	t_image		frame;
	t_image		images[4];
	t_map		*map;
	t_config	*config;
	t_game		*game;
	t_player	player;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	double		last_frame_time;
}	t_render;

/* Duvar kolonu çizimi için geçici değerler (sadece render tarafında kullanılır). */
typedef struct s_wall_column
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_index;
	int		texture_x;
	double	wall_x;
	double	step;
	double	texture_position;
}	t_wall_column;

/* -----------------------------------------------------------------------------
 *  Init (window, render, frame)
 * --------------------------------------------------------------------------- */

int		init_mlx_window(t_render *render);
int		init_render(t_render *render);
int		init_frame(t_render *render);

/* -----------------------------------------------------------------------------
 *  Ray casting
 * --------------------------------------------------------------------------- */

int		init_ray_direction(t_ray_dir *ray, t_render *render, int x);
void	calculate_delta_and_step(t_ray_dir *ray);
void	calculate_side_distance(t_ray_dir *ray, t_render *render);
void	dda_algorithm(t_ray_dir *ray, t_render *render);
double	calculate_wall_distance(t_ray_dir *ray, t_render *render);

/* -----------------------------------------------------------------------------
 *  Render / pixel
 * --------------------------------------------------------------------------- */

int		render_frame(t_render *render);
void	put_pixel_to_mem(t_image *img, int x, int y, int color);

/* -----------------------------------------------------------------------------
 *  Game loop / player movement & rotation
 * --------------------------------------------------------------------------- */

int		game_loop(t_render *render);
char	get_cell(t_map *map, double x, double y);
void	try_move(t_render *render, double nx, double ny);
void	rotate_player(t_render *render, double angle);

/* -----------------------------------------------------------------------------
 *  Wall column helpers (height, texture selection & coordinates)
 * --------------------------------------------------------------------------- */

void	init_wall_line(double perp_dist, t_render *render,
			t_wall_column *wall_column);
void	select_texture_index(t_ray_dir *ray, t_wall_column *wall_column);
double	calculate_wall_x(t_render *render, t_ray_dir *ray, double perp_dist);
void	init_texture_coords(t_render *render, t_ray_dir *ray,
			t_wall_column *wall_column);

/* -----------------------------------------------------------------------------
 *  key hooks & window close
 * --------------------------------------------------------------------------- */

int		key_press(int key, t_render *render);
int		key_release(int key, t_render *render);
int		on_close(t_render *render);

#endif