/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun <emuzun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:49:17 by emuzun            #+#    #+#             */
/*   Updated: 2024/11/03 18:10:41 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	last;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	last = ft_strlen(s1);
	if (*set == '\0')
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (last > i && ft_strchr(set, s1[last - 1]))
		last--;
	return (ft_substr(s1, i, last - i));
}
