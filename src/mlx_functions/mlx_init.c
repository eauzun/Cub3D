/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 00:59:23 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/27 02:34:10 by ecakdemi         ###   ########.fr       */
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
	printf("MLX window + frame created successfully\n");
	return (1);
}

int render_frame(t_render *render) // test için render_frame fonksiyonu ekledim, bu fonksiyon basitçe frame'i kırmızıya boyar ve pencereye çizer.
{
	(void)render;
	return 1;
	
}

int init_render(t_render *render) // Bu fonksiyon, render yapısını başlatır ve gerekli MLX işlemlerini yapar.
{
	init_mlx_window(render);
	init_frame(render);
	render_frame(render);
	return (1);
}