
#include "../../includes/exec.h"

int	ft_pwd(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 1000);
	if (!path)
		exit(1);
	if (getcwd(path, 1000))
		ft_putendl_fd(path, 1);
	else
		perror("");
	free(path);
	return (0);
}
