#ifndef RENDER_H
# define RENDER_H

# include "mlx.h"
# include <math.h>

typedef struct s_config t_config;

# define WINDOW_WIDTH  800
# define WINDOW_HEIGHT 600

# ifdef __APPLE__
#  define KEY_ESC    53
#  define KEY_W      13
#  define KEY_A      0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_LEFT   123
#  define KEY_RIGHT  124
# else
#  define KEY_ESC    65307
#  define KEY_W      119
#  define KEY_A      97
#  define KEY_S      115
#  define KEY_D      100
#  define KEY_LEFT   65361
#  define KEY_RIGHT  65363
# endif

/* X11 event codes (same on Linux and macOS with mlx) */
# define MLX_KEY_PRESS    2
# define MLX_KEY_RELEASE  3
# define MLX_DESTROY      17

typedef struct s_map      t_map;
typedef struct s_ray_dir  t_ray_dir;

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

typedef struct s_game	t_game;

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

int		init_mlx_window(t_render *render);
int		init_render(t_render *render);
int		init_frame(t_render *render);
int		render_frame(t_render *render);
void	put_pixel_to_mem(t_image *img, int x, int y, int color);
void	calculate_delta_and_step(t_ray_dir *ray);
void	calculate_side_distance(t_ray_dir *ray, t_render *render);
void	dda_algorithm(t_ray_dir *ray, t_render *render);
int		init_ray_direction(t_ray_dir *ray, t_render *render, int x);
double	calculate_wall_distance(t_ray_dir *ray, t_render *render);

#endif