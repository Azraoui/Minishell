
#include "../../includes/exec.h"

int	skipn(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int		i;

	if ((*(args + 1)) && !ft_strncmp(args[1], "-n", 2) && skipn(args[1]))
	{
		i = 2;
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				ft_putchar_fd(' ', 1);
		}
		return (1);
	}
	i = 1;
	while ((*(args + 1)) && args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (1);
}