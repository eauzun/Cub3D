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

/* Verilen (x,y) map hücresindeki karakteri döndürür; sınır dışı veya geçersiz indeks için ' ' döner. */
static char	get_cell(t_map *map, double x, double y)
{
	int	map_x_index;
	int	map_y_index;

	map_x_index = (int)x;
	map_y_index = (int)y;
	if (map_y_index < 0 || map_y_index >= map->height
		|| map_x_index < 0 || map_x_index >= map->width)
		return (' ');
	if (map_x_index >= (int)ft_strlen(map->grid[map_y_index]))
		return (' ');
	return (map->grid[map_y_index][map_x_index]);
}

/* Oyuncuyu (nx,ny) konumuna taşımaya çalışır; duvar veya boşluk varsa taşımaz. */
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

/* Oyuncu yön ve kamera düzlemini verilen açı kadar (radyan) döndürür. */
static void	rotate_player(t_render *render, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_value;
	double	sin_value;

	cos_value = cos(angle);
	sin_value = sin(angle);
	old_dir_x = render->player.dir_x;
	render->player.dir_x = render->player.dir_x * cos_value
		- render->player.dir_y * sin_value;
	render->player.dir_y = old_dir_x * sin_value
		+ render->player.dir_y * cos_value;
	old_plane_x = render->player.plane_x;
	render->player.plane_x = render->player.plane_x * cos_value
		- render->player.plane_y * sin_value;
	render->player.plane_y = old_plane_x * sin_value
		+ render->player.plane_y * cos_value;
}

/* ─── key hooks ───────────────────────────────────────────────────────────── */

/* Tuş basıldığında çağrılır: ESC ile kapatma, W/A/S/D ve oklar için bayrakları 1 yapar. */
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

/* Tuş bırakıldığında çağrılır: ilgili hareket/dönüş bayrağını 0 yapar. */
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

/* Pencere kapatıldığında veya ESC'de: render ve game kaynaklarını serbest bırakıp programı sonlandırır. */
static int	on_close(t_render *render)
{
	t_game	*game;

	game = render->game;
	free_render(render);
	free_game(game);
	exit(0);
	return (0);
}

/* MLX bağlamı ve pencere oluşturur; başarısızsa hata mesajıyla 1 döner. */
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

/* Sistem zamanını saniye cinsinden (ondalıklı) döndürür. */
static double	get_time_sec(void)
{
	struct timeval	time_value;

	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec + time_value.tv_usec / 1000000.0);
}

/* Zaman farkını hesaplar ve frame süresini mantıklı bir aralıkta tutar. */
static double	update_delta_time(t_render *render)
{
	double	now;
	double	delta_time;

	now = get_time_sec();
	delta_time = now - render->last_frame_time;
	render->last_frame_time = now;
	if (delta_time <= 0.0 || delta_time > 0.1)
		delta_time = 0.016;
	return (delta_time);
}

/* Basılı hareket tuşlarına göre oyuncunun konumunu günceller. */
static void	handle_movement(t_render *render, double move_distance)
{
	if (render->key_w)
		try_move(render,
			render->player.x + render->player.dir_x * move_distance,
			render->player.y + render->player.dir_y * move_distance);
	if (render->key_s)
		try_move(render,
			render->player.x - render->player.dir_x * move_distance,
			render->player.y - render->player.dir_y * move_distance);
	if (render->key_a)
		try_move(render,
			render->player.x - render->player.plane_x * move_distance,
			render->player.y - render->player.plane_y * move_distance);
	if (render->key_d)
		try_move(render,
			render->player.x + render->player.plane_x * move_distance,
			render->player.y + render->player.plane_y * move_distance);
}

/* Basılı dönüş tuşlarına göre oyuncunun yönünü günceller. */
static void	handle_rotation(t_render *render, double rotation_angle)
{
	if (render->key_left)
		rotate_player(render, -rotation_angle);
	if (render->key_right)
		rotate_player(render, rotation_angle);
}

/* Her frame'de çağrılır: delta time, hareket, dönüş ve bir frame çizimi yapar. */
static int	game_loop(t_render *render)
{
	double	delta_time;
	double	move_distance;
	double	rotation_angle;

	delta_time = update_delta_time(render);
	move_distance = MOVE_SPEED_PER_SEC * delta_time;
	rotation_angle = ROT_SPEED_PER_SEC * delta_time;
	handle_movement(render, move_distance);
	handle_rotation(render, rotation_angle);
	render_frame(render);
	return (0);
}

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

/* ─── ray helpers ─────────────────────────────────────────────────────────── */

/* Ekran kolonu x için ışın yönü ve başlangıç map hücresini hesaplar. */
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

/* Işın yönüne göre delta mesafe ve adım (step_x, step_y) değerlerini hesaplar. */
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

/* Işının ilk yatay/dikey grid çizgisine kadar olan yan mesafelerini hesaplar. */
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

/* DDA ile ışını ilerleterek duvara (veya harita sınırına) çarpana kadar map üzerinde adımlar. */
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

/* Oyuncudan duvara olan dik (perpendicular) uzaklığı döndürür.
 * Fish-eye etkisini önlemek için ışın uzunluğu yerine bu değer kullanılır. */
double	calculate_wall_distance(t_ray_dir *ray, t_render *render)
{
	if (ray->side == 0)
		return ((ray->map_x - render->player.x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x);
	return ((ray->map_y - render->player.y
			+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y);
}

/* ─── render frame ────────────────────────────────────────────────────────── */

/* Tek kolonda tavan ve zemin bölümlerini config renklerine göre çizer. */
static void	draw_ceiling_floor(t_render *render, int screen_x,
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

/* Duvar kolonunun ekrandaki yüksekliğini ve başlangıç/bitiş satırlarını hesaplar. */
static void	init_wall_line(double perp_dist, t_render *render,
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

/* Işının tarafına ve yönüne göre kullanılacak texture indeksini seçer. */
static void	select_texture_index(t_ray_dir *ray, t_wall_column *wall_column)
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

/* Oyuncu konumu ve ışın yönüne göre duvarın vurulduğu x konumunu hesaplar. */
static double	calculate_wall_x(t_render *render, t_ray_dir *ray,
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

/* Texture koordinatlarını (sütun, adım ve başlangıç ofseti) hesaplar. */
static void	init_texture_coords(t_render *render, t_ray_dir *ray,
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

/* Tek bir duvar kolonunu texture'tan örnekleyerek ekrana çizer. */
static void	draw_textured_column(t_render *render, int screen_x,
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
static void	draw_wall_column(t_render *render, t_ray_dir *ray,
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
	/* perp_dist: oyuncudan duvara dik uzaklık; duvar yüksekliği buna göre hesaplanır. */
	double		perp_dist;

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