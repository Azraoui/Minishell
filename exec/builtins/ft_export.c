
#include "../../includes/exec.h"

void	print_env(char **env, int fd)
{
	int		i;
	char	**line;

	i = 0;
	sort_arr_alphab(env);
	while (env[i])
	{
		line = ft_split(env[i], '=');
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(line[0], fd);
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(line[1], fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putchar_fd('\n', fd);
		split_free(line);
		i++;
	}
}

char	**insert_var(char *var, char ***env)
{
	char	**tmp;
	int		i;
	int		len;

	len = ppter_len(*env);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(*(*env + i));
		i++;
	}
	tmp[i++] = ft_strdup(var);
	tmp[i] = NULL;
	return (tmp);
}

int	find_var(char *var, char **env)
{
	char **sp_var;
	int	i;

	i = 0;
	while (env[i])
	{
		sp_var = ft_split(env[i], '=');
		if (!ft_strcmp(sp_var[0], var))
		{
			split_free(sp_var);
			return (i);
		}
		split_free(sp_var);
		i++;
	}
	return (-1);
}

int	check_var(char *var, char ***env)
{
	char	**sp_var;
	int		i;

	sp_var = ft_split(var, '=');
	i = 0;
	while (*sp_var && sp_var[0][i])
	{
		if (ft_isdigit(sp_var[0][0]) || !ft_isalnum_var(sp_var[0][i]))
		{
			ft_perror(sp_var[0], ": not a valid identifier", 1);
			split_free(sp_var);
			return (g_exit_status);
		}
		i++;
	}
	i = find_var(sp_var[0], *env);
	split_free(sp_var);
	if (i == -1)
		*env = insert_var(var, env);
	else
		*(*env + i) = var;
	return (0);
}

int	ft_export(char **args, char ***env, int fd)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (args[i] == NULL)
		print_env(*env, fd);
	while (args[i])
		ret = check_var(args[i++], env);
	return (ret);
}