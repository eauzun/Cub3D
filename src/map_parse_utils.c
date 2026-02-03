/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:15 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/03 19:01:03 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int check_file_extension(char *file_path)
{
    int len;

    len = ft_strlen(file_path);
    if (len < 4)
        return (-1);
    if (file_path[len - 4] != '.'
        || file_path[len - 3] != 'c'
        || file_path[len - 2] != 'u'
        || file_path[len - 1] != 'b')
        return (-1);
    return (0);
}

int copy_grid(t_map *map) // bu fonksiyon flood fill için yeni bir map kopyası oluşturur.
{
    int i;

    i = 0;
    map->copy_grid = malloc(sizeof(char *) * map->height);
    if (!map->copy_grid)
    {
        error_msg("malloc error");
        return (-1);
    }
    while (i < map->height)
    {
        map->copy_grid[i] = ft_strdup(map->grid[i]);
        if (!map->copy_grid[i])
        {
            error_msg("strdup error");
            return (-1);
        }
        i++;
    }
    return (0);
}
