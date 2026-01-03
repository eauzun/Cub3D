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


