/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:34:59 by emuzun            #+#    #+#             */
/*   Updated: 2024/10/22 01:37:47 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
		return (ft_memcpy(dst, src, n));
	else
		while (n--)
			((char *)dst)[n] = ((char *)src)[n];
	return (dst);
}
