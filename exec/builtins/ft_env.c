
#include "../../includes/exec.h"

int ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1] != NULL)
		return (-1);
	else
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				ft_putendl_fd(env[i], 1);
			i++;
		}
	}
	return 0;
}
