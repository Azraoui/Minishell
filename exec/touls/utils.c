
#include "../../includes/exec.h"

int		ppter_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	sort_arr_alphab(char **env)
{
	int		i;
	int		j;
	int		ret;
	char	*swap;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			ret = ft_strcmp(env[i], env[j]);
			if (ret > 0)
			{
				swap = env[j];
				env[j] = env[i];
				env[i] = swap;
			}
			j++;
		}
		i++;
	}
}

int		ft_lstat(char *path, int status)
{
	struct	stat buf;

	if (status && (*path == '.' || *path == '/'))
	{
		if (!(!lstat(path, &buf) && !(buf.st_mode & S_IFDIR)
		 	&& (buf.st_mode & S_IXUSR)))
				return (-1);
	}
	return (!lstat(path, &buf) && !(buf.st_mode & S_IFDIR)
		 && (buf.st_mode & S_IXUSR));
}

int	ft_isalnum_var(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	else
		return (0);
}
