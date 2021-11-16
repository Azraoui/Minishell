
#include "../../includes/exec.h"

char	**delet_var(char ***env, int index)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	len = ppter_len(*env);
	tmp = (char **)malloc(sizeof(char *) * len);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && (*(*env + j)))
	{
		if (j == index)
		{
			j++;
			continue ;
		}
		tmp[i++] = ft_strdup(*(*env + (j++)));
	}
	tmp[i] = NULL;
	return (tmp);
}

int	find_var_unset(char *var, char **env)
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

int	check_var_unset(char *var, char ***env)
{
	char	**sp_var;
	int		i;

	sp_var = ft_split(var, '=');
	i = 0;
	while (sp_var[0][i])
	{
		if (ft_isdigit(sp_var[0][0]) || !ft_isalnum_var(sp_var[0][i]))
		{
			split_free(sp_var);
			return (-1);
		}
		i++;
	}
	i = find_var_unset(sp_var[0], *env);
	split_free(sp_var);
	if (i != -1)
		*env = delet_var(env, i);
	return (0);
}

int	ft_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		check_var_unset(args[i], env);
		i++;
	}
	return (0);
}
