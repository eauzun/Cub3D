/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 23:58:26 by emuzun            #+#    #+#             */
/*   Updated: 2025/01/22 00:01:20 by emuzun           ###   ########.fr       */
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
