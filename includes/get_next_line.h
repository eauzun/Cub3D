#ifndef GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
#  endif

#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include"libft.h"


char *get_all_line(int fd, char *all_line);
char *till_nl(char *all_line);
char *return_rest(char *all_line);
char *get_next_line(int fd);
size_t  ft_strnl(char *s);
#endif