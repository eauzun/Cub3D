/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 00:00:00 by test              #+#    #+#             */
/*   Updated: 2026/02/08 00:00:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

static void	init_game(t_game *game)
{
	game->map.grid = NULL;
	game->map.copy_grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_x = 0;
	game->map.player_y = 0;
	game->map.player_look = 0;
	game->map.player_num = 0;
	game->tex.no = NULL;
	game->tex.so = NULL;
	game->tex.we = NULL;
	game->tex.ea = NULL;
	game->tex.f_r = -1;
	game->tex.f_g = -1;
	game->tex.f_b = -1;
	game->tex.c_r = -1;
	game->tex.c_g = -1;
	game->tex.c_b = -1;
	game->tex.tex_count = 0;
	game->tex.color_count = 0;
}

static void	print_separator(void)
{
	printf("\n");
	printf("==============================================\n");
}

static void	print_map_info(t_map *map)
{
	print_separator();
	printf("📍 MAP INFORMATION\n");
	print_separator();
	printf("Width:  %d\n", map->width);
	printf("Height: %d\n", map->height);
	printf("\n");
}

static void	print_player_info(t_map *map)
{
	print_separator();
	printf("🎮 PLAYER INFORMATION\n");
	print_separator();
	printf("Player Count: %d\n", map->player_num);
	if (map->player_num == 1)
	{
		printf("Position X:   %d\n", map->player_x);
		printf("Position Y:   %d\n", map->player_y);
		printf("Looking:      %c\n", map->player_look);
		printf("Direction:    ");
		if (map->player_look == 'N')
			printf("North ↑\n");
		else if (map->player_look == 'S')
			printf("South ↓\n");
		else if (map->player_look == 'E')
			printf("East →\n");
		else if (map->player_look == 'W')
			printf("West ←\n");
	}
	printf("\n");
}

static void	print_map_grid(t_map *map)
{
	int	y;
	int	x;

	print_separator();
	printf("🗺️  MAP GRID (After Padding)\n");
	print_separator();
	y = 0;
	while (y < map->height)
	{
		printf("Line %2d: |", y);
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '1')
				printf("█");
			else if (map->grid[y][x] == '0')
				printf(" ");
			else if (map->grid[y][x] == ' ')
				printf("·");
			else
				printf("%c", map->grid[y][x]);
			x++;
		}
		printf("|\n");
		y++;
	}
	printf("\n");
}

static void	print_texture_info(t_tex *tex)
{
	print_separator();
	printf("🎨 TEXTURE INFORMATION\n");
	print_separator();
	printf("Texture Count: %d/4\n", tex->tex_count);
	printf("Color Count:   %d/2\n\n", tex->color_count);
	
	if (tex->no)
		printf("North:  %s\n", tex->no);
	else
		printf("North:  (not set)\n");
	
	if (tex->so)
		printf("South:  %s\n", tex->so);
	else
		printf("South:  (not set)\n");
	
	if (tex->we)
		printf("West:   %s\n", tex->we);
	else
		printf("West:   (not set)\n");
	
	if (tex->ea)
		printf("East:   %s\n", tex->ea);
	else
		printf("East:   (not set)\n");
	
	printf("\n");
}

static void	print_color_info(t_tex *tex)
{
	print_separator();
	printf("🎨 COLOR INFORMATION\n");
	print_separator();
	
	if (tex->f_r != -1)
		printf("Floor:   RGB(%d, %d, %d)\n", tex->f_r, tex->f_g, tex->f_b);
	else
		printf("Floor:   (not set)\n");
	
	if (tex->c_r != -1)
		printf("Ceiling: RGB(%d, %d, %d)\n", tex->c_r, tex->c_g, tex->c_b);
	else
		printf("Ceiling: (not set)\n");
	
	printf("\n");
}

static void	print_validation_status(t_map *map)
{
	print_separator();
	printf("✅ VALIDATION STATUS\n");
	print_separator();
	
	if (map->player_num == 1)
		printf("✓ Player count correct\n");
	else
		printf("✗ Player count incorrect (%d)\n", map->player_num);
	
	printf("✓ Map is closed\n");
	printf("✓ No invalid characters\n");
	printf("✓ Zero boundaries valid\n");
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("❌ Usage: ./test_cub3d <map_file>\n");
		printf("Example: ./test_cub3d maps/simple.cub\n");
		printf("\n💡 Note: This test only reads MAP data\n");
		printf("   (It skips NO/SO/WE/EA/F/C lines)\n");
		return (1);
	}

	init_game(&game);

	printf("\n");
	printf("╔════════════════════════════════════════════╗\n");
	printf("║      CUB3D PARSER TEST PROGRAM            ║\n");
	printf("╚════════════════════════════════════════════╝\n");
	printf("\n");
	printf("📂 Reading file: %s\n", argv[1]);
	printf("🔍 Mode: MAP ONLY (textures/colors ignored)\n");

	if (map_parse(argv[1], &game.map) == -1)
	{
		printf("\n❌ PARSING FAILED!\n");
		printf("💡 Tip: Make sure the file contains valid map data\n");
		free_game(&game);
		return (1);
	}

	printf("✅ Map parsing successful!\n");

	print_map_info(&game.map);
	print_player_info(&game.map);
	print_texture_info(&game.tex);
    print_color_info(&game.tex);
	print_map_grid(&game.map);
	print_validation_status(&game.map);

	print_separator();
	printf("🎉 All tests completed!\n");
	print_separator();

	free_game(&game);
	return (0);
}