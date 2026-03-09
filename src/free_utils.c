/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:12 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/01 00:00:00 by emuzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


/* Tek bir texture path pointer'ını serbest bırakıp NULL yapar. */
static void	free_texture_path(char **path)
{
	if (*path)
	{
		free(*path);
		*path = NULL;
	}
}

/* Config'teki dört texture path'ini serbest bırakır. */
void	free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture_path(&config->no);
	free_texture_path(&config->so);
	free_texture_path(&config->we);
	free_texture_path(&config->ea);
}


/* Dört duvar texture görselini MLX ile yok eder. */
static void	free_texture_images(t_render *render)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (render->images[i].mlx_img)
		{
			mlx_destroy_image(render->mlx, render->images[i].mlx_img);
			render->images[i].mlx_img = NULL;
		}
		i++;
	}
}

/* Frame görselini, pencereyi ve MLX display'ini yok edip mlx pointer'ını serbest bırakır. */
static void	free_frame_and_window(t_render *render)
{
	if (render->frame.mlx_img)
	{
		mlx_destroy_image(render->mlx, render->frame.mlx_img);
		render->frame.mlx_img = NULL;
	}
	if (render->window)
	{
		mlx_destroy_window(render->mlx, render->window);
		render->window = NULL;
	}
	if (render->mlx)
	{
		mlx_destroy_display(render->mlx);
		free(render->mlx);
		render->mlx = NULL;
	}
}

