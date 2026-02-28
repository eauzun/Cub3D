/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:59:23 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/28 02:38:37 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "render.h"
#include <stdio.h>
#include <sys/time.h>

static char	get_cell(t_map *map, double x, double y)
{
	int	ix;
	int	iy;
	int	row_len;

	ix = (int)x;
	iy = (int)y;
	if (iy < 0 || iy >= map->height || ix < 0 || ix >= map->width)
		return (' ');
	row_len = ft_strlen(map->grid[iy]);
	if (ix >= row_len)
		return (' ');
	return (map->grid[iy][ix]);
}

static void	try_move(t_render *render, double nx, double ny)
{
	char	c;

	c = get_cell(render->map, nx, render->player.y);
	if (c != '1' && c != ' ' && c != '\0')
		render->player.x = nx;
	c = get_cell(render->map, render->player.x, ny);
	if (c != '1' && c != ' ' && c != '\0')
		render->player.y = ny;
}

#define MOVE_SPEED_PER_SEC 2.0
#define ROT_SPEED_PER_SEC  2.0

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
	render->player.plane_x = render->player.plane_x * c - render->player.plane_y * s;
	render->player.plane_y = old_plane_x * s + render->player.plane_y * c;
}

int init_mlx_window(t_render *render) // Bu fonksiyon, MLX kütüphanesini başlatır ve bir pencere oluşturur.
{
	render->mlx = mlx_init();
	if (!render->mlx)
		return (exit_check("MLX initialization failed", 1, 1, NULL));
	render->window = mlx_new_window(render->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!render->window)
	{
		//mlx_destroy_display(render->mlx); ->linux'ta bu fonksiyon var ama macOS'ta yok, bu yüzden sadece mlx'yi freeledim.
		free(render->mlx);
		return (exit_check("MLX window creation failed", 1, 1, NULL));
	}
	printf("MLX window created successfully\n");
	return (1);
}

/* KeyPress: event 2 (macOS), KeyRelease: event 3 */
#define MLX_KEY_PRESS   2
#define MLX_KEY_RELEASE 3

static int	key_press(int key, t_render *render)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(render->mlx, render->window);
		exit(0);
	}
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
	double	move_step;
	double	rot_angle;

	now = get_time_sec();
	dt = now - render->last_frame_time;
	render->last_frame_time = now;
	if (dt <= 0.0 || dt > 0.1)
		dt = 0.016;
	move_step = MOVE_SPEED_PER_SEC * dt;
	rot_angle = ROT_SPEED_PER_SEC * dt;
	if (render->key_w)
		try_move(render,
			render->player.x + render->player.dir_x * move_step,
			render->player.y + render->player.dir_y * move_step);
	if (render->key_s)
		try_move(render,
			render->player.x - render->player.dir_x * move_step,
			render->player.y - render->player.dir_y * move_step);
	if (render->key_a)
		try_move(render,
			render->player.x - render->player.plane_x * move_step,
			render->player.y - render->player.plane_y * move_step);
	if (render->key_d)
		try_move(render,
			render->player.x + render->player.plane_x * move_step,
			render->player.y + render->player.plane_y * move_step);
	if (render->key_left)
		rotate_player(render, -rot_angle);
	if (render->key_right)
		rotate_player(render, rot_angle);
	render_frame(render);
	return (0);
}

void put_pixel_to_mem(t_image *img, int x, int y, int color) //texture'leri çizerken kullanacağımız fonksiyon, bu fonksiyon, verilen x ve y koordinatlarına belirtilen renkte bir piksel çizer. Bu, doğrudan görüntü belleğine yazma işlemi yaparak hızlı bir şekilde piksel renklerini değiştirmemizi sağlar.
{ // ******************* y satır indexi, x sütun indexi. **********************
	char *dest;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height) //ekran sınır kontroli
		return ;
	dest = img->mlx_addr + (y * img->mlx_line_length + x * (img->mlx_bits_per_pixel / 8)); //dest, çizilecek pikselin bellekteki adresini hesaplar. y * mlx_line_length ile satır başına atlanır, x * (bits_per_pixel / 8) ile de sütun başına atlanır.
	*(unsigned int *)dest = color; //color'ü doğrudan belleğe yazıyoruz, bu sayede hızlı bir şekilde piksel renklerini değiştirebiliyoruz.
}

int init_frame(t_render *render)
{
	// Bu fonksiyon, render yapısındaki frame'i başlatmak için kullanılabilir.
	// Örneğin, mlx_new_image ile yeni bir görüntü oluşturabilir ve frame'e atayabilirsiniz.
	render->frame.mlx_img = mlx_new_image(render->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!render->frame.mlx_img)
		return (exit_check("MLX image creation failed", 1, 1, NULL));
	render->frame.mlx_addr = mlx_get_data_addr(render->frame.mlx_img, &render->frame.mlx_bits_per_pixel, &render->frame.mlx_line_length, &render->frame.mlx_endian);
	if (!render->frame.mlx_addr)
	{
		mlx_destroy_image(render->mlx, render->frame.mlx_img);
		return (exit_check("MLX get data address failed", 1, 1, NULL));
	}
	render->frame.height = WINDOW_HEIGHT;
	render->frame.width = WINDOW_WIDTH;
	printf("MLX window + frame created successfully\n");
	return (1);
}

int init_ray_direction(t_ray_dir *ray, t_render *render, int x) // Bu fonksiyon, verilen x koordinatına göre ray yönünü hesaplar. Bu, raycasting işlemi için gerekli olan bilgileri sağlar.
{
	double camera_x = 2 * x / (double)render->frame.width - 1; // Kolonun kamera üzerindeki konumu (-1 ile +1 arası)
	ray->ray_dir_x = render->player.dir_x + render->player.plane_x * camera_x; // Bu kolonun ray yönü
	ray->ray_dir_y = render->player.dir_y + render->player.plane_y * camera_x;

	ray->map_x = (int)render->player.x; //Hangi harita karesinde olduğumuzu bulmak için oyuncunun konumunu tam sayıya yuvarlıyoruz.
	ray->map_y = (int)render->player.y;
	ray->hit = 0; //Henüz bir duvara çarpmadık, bu yüzden hit'i 0 olarak başlatıyoruz.
	return (0);
}


void dda_algorithm(t_ray_dir *ray, t_render *render)
{
	//ray x yönüne mi daha yakın y yönüne mi? Ona göre bir sonraki grid hücresine geç. O hücre duvar mı? Değil mi? diye kontrol et. Duvara çarpmadıysak bu işlemi tekrarla. Duvarsa dur.
	while (ray->hit == 0) // DDA algoritması, ray'in harita üzerinde ilerleyerek duvara çarpana kadar hangi karelerden geçtiğini belirler. Bu algoritma, ray'in x ve y yönlerinde ne kadar ilerlemesi gerektiğini hesaplar ve ray'i adım adım hareket ettirir.
	{
		if (ray->side_dist_x < ray->side_dist_y)  //side_dist_x = ray'in bir sonraki dikey grid çizgisine olan mesafesi, side_dist_y = ray'in bir sonraki yatay grid çizgisine olan mesafesi. Hangisi daha küçükse o yönde bir adım atılır.
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Dikey duvara çarptık, x duvarı
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Yatay duvara çarptık, y duvarı
		}
		if (ray->map_y < 0 || ray->map_y >= render->map->height || ray->map_x < 0 || ray->map_x >= render->map->width)
		{
			/* Out of bounds -> treat as hit to avoid invalid memory access */
			ray->hit = 1;
			break;
		}
		if (render->map->grid[ray->map_y][ray->map_x] == '1') // Harita karesinde '1' varsa duvara çarpmışız demektir.
			ray->hit = 1;
	}
}

void calculate_side_distance(t_ray_dir *ray, t_render *render)
{
	if (ray->ray_dir_x < 0) //ray sola gidiyor mu? Evet ise, oyuncunun x konumundan map_x'e olan mesafeyi delta_dist_x ile çarparak side_dist_x'i hesaplıyoruz. Bu, ray'in bir sonraki dikey grid çizgisine olan mesafesini verir.
		ray->side_dist_x = (render->player.x - ray->map_x) * ray->delta_dist_x; // Ray sola gidiyor, bu yüzden oyuncunun x konumundan map_x'e olan mesafeyi delta_dist_x ile çarparak side_dist_x'i hesaplıyoruz.
	else
		ray->side_dist_x = (ray->map_x + 1.0 - render->player.x) * ray->delta_dist_x; // Ray sağa gidiyor, bu yüzden map_x + 1'den oyuncunun x konumunu çıkararak mesafeyi delta_dist_x ile çarparak side_dist_x'i hesaplıyoruz.
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = (render->player.y - ray->map_y) * ray->delta_dist_y; // Ray yukarı gidiyor, bu yüzden oyuncunun y konumundan map_y'e olan mesafeyi delta_dist_y ile çarparak side_dist_y'i hesaplıyoruz.
	else
		ray->side_dist_y = (ray->map_y + 1.0 - render->player.y) * ray->delta_dist_y; // Ray aşağı gidiyor, bu yüzden map_y + 1'den oyuncunun y konumunu çıkararak mesafeyi delta_dist_y ile çarparak side_dist_y'i hesaplıyoruz.
}

void calculate_delta_and_step(t_ray_dir *ray)
{
	//delta_dist_x ve delta_dist_y, ray'in x ve y yönlerinde bir birim hareket etmesi için gereken mesafeyi temsil eder. Bu, raycasting algoritmasında DDA (Digital Differential Analysis) adımında kullanılır.
	//step_x ve step_y, ray'in x ve y yönlerinde hangi yönde hareket edeceğini belirtir. Eğer ray negatif x yönünde hareket ediyorsa step_x -1, pozitif x yönünde hareket ediyorsa step_x 1 olur. Aynı şekilde y yönü için de geçerlidir.
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // Sonsuz gibi büyük bir değer, böylece hiç x yönünde hareket olmaz.
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // Ray'in x yönünde bir birim hareket etmesi için gereken mesafe.
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30; // Sonsuz gibi büyük bir değer, böylece hiç y yönünde hareket olmaz.
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y); // Ray'in y yönünde bir birim hareket etmesi için gereken mesafe.
	if (ray->ray_dir_x < 0)
		ray->step_x = -1; // Ray sola gidiyor, bu yüzden x adımını -1 yapıyoruz.
	else
		ray->step_x = 1; // Ray sağa gidiyor, bu yüzden x adımını 1 yapıyoruz.
	if (ray->ray_dir_y < 0)
		ray->step_y = -1; // Ray yukarı gidiyor, bu yüzden y adımını -1 yapıyoruz.
	else
		ray->step_y = 1; // Ray aşağı gidiyor, bu yüzden y adımını 1 yapıyoruz.
}

int render_frame(t_render *render) // test için render_frame fonksiyonu ekledim, bu fonksiyon basitçe frame'i kırmızıya boyar ve pencereye çizer.
{
	int x;
	t_ray_dir ray;
	double perp_dist;
	int line_height;
	int draw_start;
	int draw_end;
	int tex_num;

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
		line_height = (int)(render->frame.height / perp_dist);
		draw_start = -line_height / 2 + render->frame.height / 2;
		draw_end = line_height / 2 + render->frame.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= render->frame.height)
			draw_end = render->frame.height - 1;

		/* select texture: images[0]=NO,1=SO,2=WE,3=EA */
		if (ray.side == 0)
		{
			if (ray.ray_dir_x > 0)
				tex_num = 2; /* WE */
			else
				tex_num = 3; /* EA */
		}
		else
		{
			if (ray.ray_dir_y > 0)
				tex_num = 0; /* NO */
			else
				tex_num = 1; /* SO */
		}

		/* calculate exact position where wall was hit */
		double wall_x;
		if (ray.side == 0)
			wall_x = render->player.y + perp_dist * ray.ray_dir_y;
		else
			wall_x = render->player.x + perp_dist * ray.ray_dir_x;
		wall_x -= floor(wall_x);

		t_image *tex = &render->images[tex_num];
		int tex_x = (int)(wall_x * (double)tex->width);
		if (ray.side == 0 && ray.ray_dir_x > 0)
			tex_x = tex->width - tex_x - 1;
		if (ray.side == 1 && ray.ray_dir_y < 0)
			tex_x = tex->width - tex_x - 1;

		double step = 1.0 * tex->height / line_height;
		double tex_pos = (draw_start - render->frame.height / 2 + line_height / 2) * step;

		int y = draw_start;
		while (y <= draw_end)
		{
			int tex_y = (int)tex_pos & (tex->height - 1);
			tex_pos += step;
			char *src = tex->mlx_addr + (tex_y * tex->mlx_line_length + tex_x * (tex->mlx_bits_per_pixel / 8));
			unsigned int color = *(unsigned int *)src;
			put_pixel_to_mem(&render->frame, x, y, color);
			y++;
		}

		/* draw ceiling and floor from .cub F and C RGB */
		{
			int	ceiling_rgb;
			int	floor_rgb;

			ceiling_rgb = (render->config->ceiling.r << 16)
				| (render->config->ceiling.g << 8)
				| render->config->ceiling.b;
			floor_rgb = (render->config->floor.r << 16)
				| (render->config->floor.g << 8)
				| render->config->floor.b;
			y = 0;
			while (y < draw_start)
			{
				put_pixel_to_mem(&render->frame, x, y, ceiling_rgb);
				y++;
			}
			y = draw_end + 1;
			while (y < render->frame.height)
			{
				put_pixel_to_mem(&render->frame, x, y, floor_rgb);
				y++;
			}
		}

		x++;
	}
	mlx_put_image_to_window(render->mlx, render->window, render->frame.mlx_img, 0, 0);
	return (1);
}

double calculate_wall_distance(t_ray_dir *ray, t_render *render)
{
	double wall_dist;
	if (ray->side == 0)
		wall_dist = (ray->map_x - render->player.x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		wall_dist = (ray->map_y - render->player.y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	return (wall_dist);
}

int init_render(t_render *render) // Bu fonksiyon, render yapısını başlatır ve gerekli MLX işlemlerini yapar.
{
	render->key_w = 0;
	render->key_s = 0;
	render->key_a = 0;
	render->key_d = 0;
	render->key_left = 0;
	render->key_right = 0;
	render->last_frame_time = 0.0;
	init_mlx_window(render);
	init_frame(render);
	mlx_hook(render->window, MLX_KEY_PRESS, 0, key_press, render);
	mlx_hook(render->window, MLX_KEY_RELEASE, 0, key_release, render);
	mlx_loop_hook(render->mlx, game_loop, render);

	/* load wall textures from config (NO, SO, WE, EA) */
	if (render->config)
	{
		int w, h;
		char *paths[4];
		char *names[4] = {"NO", "SO", "WE", "EA"};
		paths[0] = render->config->no;
		paths[1] = render->config->so;
		paths[2] = render->config->we;
		paths[3] = render->config->ea;
		for (int i = 0; i < 4; i++)
		{
			if (!paths[i])
				exit_check("texture: missing path", 1, -1, NULL);
			fprintf(stderr, "Loading texture %s: %s\n", names[i], paths[i]);
			render->images[i].mlx_img = mlx_xpm_file_to_image(render->mlx, paths[i], &w, &h);
			if (!render->images[i].mlx_img)
				exit_check("texture: failed to load XPM", 1, -1, NULL);
			render->images[i].mlx_addr = mlx_get_data_addr(render->images[i].mlx_img, &render->images[i].mlx_bits_per_pixel, &render->images[i].mlx_line_length, &render->images[i].mlx_endian);
			render->images[i].width = w;
			render->images[i].height = h;
			fprintf(stderr, "  Loaded: %dx%d, addr=%p\n", w, h, render->images[i].mlx_addr);
		}
	}

	/* initial render call */
	render_frame(render);
	return (1);
}