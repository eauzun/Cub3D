/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:45:47 by emuzun            #+#    #+#             */
/*   Updated: 2024/11/04 21:39:07 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*des;

	len = ft_strlen(s) + 1;
	des = malloc(sizeof(char) * len);
	if (!des)
		return (NULL);
	return (ft_memmove(des, s, len));
}
