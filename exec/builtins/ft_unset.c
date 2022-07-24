/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:42 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:30:32 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	split_free(*env);
	return (tmp);
}

int	find_var_unset(char *var, char **env)
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

int	check_var_unset(char *var, char ***env)
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
			return (g_var.ex_sts);
		}
		i++;
	}
	i = find_var_unset(sp_var[0], *env);
	split_free(sp_var);
	if (i != -1)
		*env = delet_var(env, i);
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	*ret;

	i = 1;
	ret = malloc(sizeof(int) * ppter_len(args));
	while (*(args + i) && args[i])
	{
		ret[i] = check_var_unset(args[i], env);
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
