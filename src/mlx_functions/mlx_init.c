/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:59:23 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/27 13:49:05 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdio.h>

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

void put_pixel_to_mem(t_image *img, int x, int y, int color) //texture'leri çizerken kullanacağımız fonksiyon, bu fonksiyon, verilen x ve y koordinatlarına belirtilen renkte bir piksel çizer. Bu, doğrudan görüntü belleğine yazma işlemi yaparak hızlı bir şekilde piksel renklerini değiştirmemizi sağlar.
{ // y satır indexi, x sütun indexi.
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


int render_frame(t_render *render) // test için render_frame fonksiyonu ekledim, bu fonksiyon basitçe frame'i kırmızıya boyar ve pencereye çizer.
{
	int x;
	int y;
	int line_height = 150;
	int start;
	int end;

	x = 0;
	while (x < render->frame.width)
	{
		start = render->frame.height / 2 - line_height / 2;
		end = render->frame.height / 2 + line_height / 2;
		y = start;
		while (y < end)
		{
			put_pixel_to_mem(&render->frame, x, y, 0xFF0000); // Kırmızı renk
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(render->mlx, render->window, render->frame.mlx_img, 0, 0);
	return (1);
}

int init_render(t_render *render) // Bu fonksiyon, render yapısını başlatır ve gerekli MLX işlemlerini yapar.
{
	init_mlx_window(render);
	init_frame(render);
	render_frame(render);
	return (1);
}