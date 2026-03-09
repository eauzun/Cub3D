
#include "../includes/cub3d.h"

/* Map grid'ini satır satır ve grid pointer'ını serbest bırakır; map alanlarını sıfırlar. */
void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (y < map->height)
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

/* İki boyutlu char dizisini (height satır) serbest bırakır. */
void	free_grid(char **map, int height)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < height)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

/* Oyun yapısını temizler: current_line, copy_grid, map ve config. */
void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	if (game->map.copy_grid)
	{
		free_grid(game->map.copy_grid, game->map.height);
		game->map.copy_grid = NULL;
	}
	free_map(&game->map);
	free_config(&game->config);
}

/* Tüm render kaynaklarını serbest bırakır: texture görselleri, frame, pencere, MLX. */
void	free_render(t_render *render)
{
	if (!render)
		return ;
	free_texture_images(render);
	free_frame_and_window(render);
}
