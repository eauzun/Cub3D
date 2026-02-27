#ifndef RENDER_H
# define RENDER_H

#include "cub3d.h"
#include <../mlx/mlx.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct s_map t_map;

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
} t_render;

int init_mlx_window(t_render *render);
int init_render(t_render *render);
int init_frame(t_render *render);
int render_frame(t_render *render);
void put_pixel_to_mem(t_image *img, int x, int y, int color);




#endif