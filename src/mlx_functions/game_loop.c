/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:39:26 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 15:41:57 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
int	game_loop(t_render *render)
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
