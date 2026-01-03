#include "../includes/cub3d.h"


static void	remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
		i++;
	}
}

static int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static int	read_map_lines(int fd, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		map->grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	return (0);
}

int	map_parse(char *file_path, t_map *map)
{
	int	fd;

	if (check_file_extension(file_path) == -1)
		return (-1);
	map->height = count_lines(file_path);
	if (map->height <= 0)
		return (-1);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (-1);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		free(map->grid);
		return (-1);
	}
	if (read_map_lines(fd, map) == -1)
	{
		free(map->grid);
		close(fd);
		return (-1);
	}
	map->width = ft_strlen(map->grid[0]);
	close(fd);
	return (0);
}

