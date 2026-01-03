/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:58:32 by emuzun            #+#    #+#             */
/*   Updated: 2025/01/22 00:03:03 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_all_line(int fd, char *all_line)
{
	char	*str;
	int		read_byte;
	char	*temp;

	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	read_byte = 1;
	while (ft_strnl(all_line) != 1 && read_byte != 0)
	{
		read_byte = read(fd, str, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(all_line);
			free(str);
			return (NULL);
		}
		temp = all_line;
		str[read_byte] = '\0';
		all_line = ft_strjoin(temp, str);
		free(temp);
	}
	free(str);
	return (all_line);
}

char	*till_nl(char *all_line)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!all_line[i])
		return (0);
	while (all_line[i] != '\n' && all_line[i] != '\0')
		i++;
	if (all_line[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (0);
	i = 0;
	while (all_line[i] != '\n' && all_line[i] != '\0')
	{
		line[i] = all_line[i];
		i++;
	}
	if (all_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*return_rest(char *all_line)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (all_line[i] != '\n' && all_line[i] != '\0')
		i++;
	if (all_line[i] == '\0')
	{
		free(all_line);
		return (0);
	}
	ret = malloc(ft_strlen(all_line) - i + 1);
	if (!ret)
		return (0);
	i++;
	j = 0;
	while (all_line[i] != '\0')
		ret[j++] = all_line[i++];
	ret[j] = '\0';
	free(all_line);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*all_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!all_line)
		all_line = ft_strdup("");
	all_line = get_all_line(fd, all_line);
	if (!all_line)
		return (0);
	line = till_nl(all_line);
	all_line = return_rest(all_line);
	return (line);
}
