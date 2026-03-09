/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:30:30 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 17:43:59 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	key_press(int key, t_render *render)
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

int	key_release(int key, t_render *render)
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

int	on_close(t_render *render)
{
	t_game	*game;

	game = render->game;
	free_render(render);
	free_game(game);
	exit(0);
	return (0);
}

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
