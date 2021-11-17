
#include "../../includes/exec.h"

int ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (*(args + 1) != NULL)
	{
		ft_perror(*(args + 1), ": No such file or directory", 127);
		exit(g_exit_status);
	}
	else
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				ft_putendl_fd(env[i], 1);
			i++;
		}
	}
	return (0);
}
