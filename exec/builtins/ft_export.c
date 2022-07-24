/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:30 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:28:06 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	print_env(char **env, int fd)
{
	int		i;
	char	**line;
	char	*tmp;

	i = 0;
	sort_arr_alphab(env);
	while (env[i])
	{
		line = ft_split(env[i], '=');
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(line[0], fd);
		tmp = ft_strchr(env[i], '=');
		if (tmp)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp + 1, fd);
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
	split_free(*env);
	return (tmp);
}

int	find_var(char *var, char **env)
{
	char	**sp_var;
	int		i;

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
	i = -1;
	while (*sp_var && sp_var[0][++i])
	{
		if (ft_isdigit(sp_var[0][0]) || !ft_isalnum_var(sp_var[0][i]))
		{
			ft_perror(sp_var[0], ": not a valid identifier", 1);
			split_free(sp_var);
			return (g_var.ex_sts);
		}
	}
	i = find_var(sp_var[0], *env);
	if (i == -1)
		*env = insert_var(var, env);
	else
		export_norm(var, i, env, sp_var[1]);
	split_free(sp_var);
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}

int	ft_export(char **args, char ***env, int fd)
{
	int	i;
	int	*ret;

	i = 1;
	ret = malloc(sizeof(int) * ppter_len(args));
	if (*(args + i) == NULL)
		print_env(*env, fd);
	while (*(args + i) && args[i])
	{
		ret[i] = check_var(args[i], env);
		i++;
	}
	i = 0;
	while (++i < ppter_len(args))
	{
		if (ret[i])
		{
			g_var.ex_sts = ret[i];
			free(ret);
			return (g_var.ex_sts);
		}
	}
	free(ret);
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}
