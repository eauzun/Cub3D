/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:21:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/02/06 22:05:44 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//return -1 olan her yerde geçmişteki şeyleri freelemeyi unutma!


int main(int argc, char **argv)
{
    t_map map;

    if (argc != 2)
    {
        write(2, "Usage: ./cub3d <map_file>\n", 27);
        return (1);
    }

    //bu error msglar yeni dosyaya taşınacak.
    // uzantılar için .cub olmayanları check_file_extension'dan kontrol edip error mesajı döndürebilir.
    //main->check_validation -> iç içe diğer check'ler -> ileride .h'da ayarlanacak error msg döndülerine göre 
    //error_msg modifiye edilerek int	error_msg(char *msg, int status) ile mevcut statuse göre error msg döndürebilir

    if (map_parse(argv[1], &map) == -1) //bu kalkıcak
    {
        write(2, "Failed to parse map\n", 20);
        return (1);
    }

    int y = 0;
    while (y < map.height)
    {
        write(1, map.grid[y], map.width);
        write(1, "\n", 1);
        y++;
    }

    free_map(&map);
    return (0);
}

