/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuzun < emuzun@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:28:22 by ecakdemi          #+#    #+#             */
/*   Updated: 2026/03/09 19:51:42 by emuzun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*get_all_line(int fd, char *all_line);
char	*till_nl(char *all_line);
char	*return_rest(char *all_line);
char	*get_next_line(int fd);
size_t	ft_strnl(char *s);
char	*extract_line(char **all_line);
#endif