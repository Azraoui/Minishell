
#include "../../includes/exec.h"

int		ft_perror(char *cmd, char *message, int error)
{
	ft_putstr_fd("Minish: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
	g_exit_status = error;
	return (error);
}