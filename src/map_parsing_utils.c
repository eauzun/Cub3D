
#include "../includes/cub3d.h"

/* NO/SO/WE/EA texture satırını parse edip config'e path yazar; tanınmazsa -1 döner. */
int	parse_texture(char *line, t_game *game)
{
	char	**target;
	char	*val;

	target = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
		target = &game->config.no;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		target = &game->config.so;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		target = &game->config.we;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		target = &game->config.ea;
	else
		return (-1);
	if (*target)
		parse_error(-1, game, "texture: duplicate identifier");
	val = get_value(line, 3);
	if (*val == '\0')
		parse_error(-1, game, "texture: path is empty");
	if (check_xpm_extension(val) == -1)
		parse_error(-1, game, "texture: must be a .xpm file");
	*target = ft_strdup(val);
	if (!*target)
		parse_error(-1, game, "texture: memory error");
	return (0);
}

/* Satırın texture veya renk identifier ile başlayıp başlamadığını kontrol eder; başlıyorsa 1 döner. */
static int	is_header_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (1);
	return (0);
}
/* Verilen string içindeki virgül sayısını döndürür (renk parse için). */
int	check_num_of_commas(char *str)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			num++;
		i++;
	}
	return (num);
}

/* Texture path'inin .xpm uzantısıyla bitip bitmediğini kontrol eder; geçerliyse 0, değilse -1 döner. */
int	check_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (-1);
	if (path[len - 4] != '.'
		|| path[len - 3] != 'x'
		|| path[len - 2] != 'p'
		|| path[len - 1] != 'm')
		return (-1);
	return (0);
}
