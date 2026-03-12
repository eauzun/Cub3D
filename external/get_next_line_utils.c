/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:58:26 by emuzun            #+#    #+#             */
/*   Updated: 2026/03/12 18:30:17 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strnl(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*extract_line(char **all_line)
{
	char	*line;
	char	*tmp;

	line = till_nl(*all_line);
	tmp = return_rest(*all_line);
	*all_line = tmp;
	if (!line && *all_line)
	{
		free(*all_line);
		*all_line = NULL;
	}
	return (line);
}
