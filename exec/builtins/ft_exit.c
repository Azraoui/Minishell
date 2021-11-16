
#include "../../includes/exec.h"

int ft_exit(char **args)
{
	if (args)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	return 0;
}