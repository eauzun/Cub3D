/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_and_cam.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:29:25 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 13:50:14 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/* ─── movement helpers ────────────────────────────────────────────────────── */

/* Verilen (x,y) map hücresindeki karakteri döndürür; sınır dışı veya geçersiz indeks için ' ' döner. */
char	get_cell(t_map *map, double x, double y)
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
void	try_move(t_render *render, double nx, double ny)
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
void	rotate_player(t_render *render, double angle)
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
