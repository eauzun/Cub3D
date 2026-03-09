/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:37:11 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:37:18 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_texture_path(char **path)
{
	if (*path)
	{
		free(*path);
		*path = NULL;
	}
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture_path(&config->no);
	free_texture_path(&config->so);
	free_texture_path(&config->we);
	free_texture_path(&config->ea);
}

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
