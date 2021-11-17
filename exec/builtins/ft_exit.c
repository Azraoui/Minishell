
#include "../../includes/exec.h"

int	find_numeric(char *s)
{
	int	i;

	i = 0;
	if (ft_strchr("+-", *s))
		s++;
	while (*s)
	{
		if (!ft_strchr("0123456789", *s))
			return (0);
		s++;
	}
	return (1);
}

int ft_exit(char **args)
{
	if (!*(args + 1))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (!find_numeric(*(args + 1)))
	{
		ft_putendl_fd("exit", 1);
		ft_perror(*args, ": numeric argument required", 255);
		exit(g_exit_status);
	}
	else if (ppter_len(args) == 2)
	{
		g_exit_status = (unsigned char)ft_atoi(*(args + 1));
		ft_putendl_fd("exit", 1);
		exit(g_exit_status);
	}
	else
	{
		ft_perror(*args, ": too many arguments", 1);
		return(g_exit_status);
	}
}