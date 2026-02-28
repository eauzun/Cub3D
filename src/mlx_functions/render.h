#ifndef RENDER_H
# define RENDER_H

#include <../mlx/mlx.h>
#include <math.h>

typedef struct s_config t_config;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

typedef struct s_map t_map;
typedef struct s_ray_dir t_ray_dir;

typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_image
{
	void *mlx_img; //mlxin tuttuğu görüntü
	char *mlx_addr; //Image buffer’ın RAM’deki başlangıç adresi
	int mlx_bits_per_pixel; //Her pikselin kaç bit olduğunu belirtir
	int mlx_line_length; //Her satırın bellekte kaç byte yer kapladığını belirtir. bu olmadan yatayda ilerlerken doğru adresi bulamayız (y)
	int mlx_endian; //Endian, çok baytlı verilerin bellekte nasıl düzenlendiğini belirtir. 0 ise little-endian, 1 ise big-endian olduğunu gösterir. Bellekte renklerin sıralamasını söylemek için var. Little-endian ise renkler sırasıyla: mavi, yeşil, kırmızı, big-endian ise kırmızı, yeşil, mavi şeklindedir.
	int width; //Görüntünün genişliği
	int height; //Görüntünün yüksekliği
} t_image;


typedef struct s_render
{
	void *mlx; //MLX kütüphanesinin ana yapısı, grafik işlemleri için gerekli olan temel yapı
	void *window; //Oluşturulan pencereyi temsil eder, grafiklerin çizileceği alan
	t_image frame; //ekrana basılacak ana görüntüyü *ramde* tutar, bu yapı, çizim işlemleri için gerekli olan bilgileri içerir, o anki frame'in nihai çıktısı. raycasting işlemi sonucunda oluşturulan görüntüyü temsil eder.
	t_image images[4]; //Texture'leri tutar, bu yapı, çizim işlemleri için gerekli olan bilgileri içerir, oyun içindeki duvarların ve diğer nesnelerin görsellerini temsil eder.
	t_map *map; //Oyun haritasını temsil eder, bu yapı, harita verilerini içerir ve çizim işlemleri sırasında kullanılır.
	t_config *config; // pointer to parsed textures/colors in game config
	t_player player; //Oyuncu konumunu ve yönünü temsil eder, bu yapı, oyuncunun hareketlerini ve bakış yönünü içerir ve çizim işlemleri sırasında kullanılır.
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
	int	key_left;
	int	key_right;
	double	last_frame_time;
} t_render;

int init_mlx_window(t_render *render);
int init_render(t_render *render);
int init_frame(t_render *render);
int render_frame(t_render *render);
void put_pixel_to_mem(t_image *img, int x, int y, int color);
void calculate_delta_and_step(t_ray_dir *ray);
void calculate_side_distance(t_ray_dir *ray, t_render *render);
void dda_algorithm(t_ray_dir *ray, t_render *render);
int init_ray_direction(t_ray_dir *ray, t_render *render, int x);
double calculate_wall_distance(t_ray_dir *ray, t_render *render);



#endif