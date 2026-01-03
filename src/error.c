int	error_msg(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}
