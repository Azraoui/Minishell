/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:04 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:30:08 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	chdir_help2(char **env, char **old_path, char **new_path)
{
	*old_path = ft_getenv_exec(env, "PWD");
	if (*old_path == NULL)
		*old_path = ft_strdup("");
	if (chdir(*new_path) == -1)
	{
		free(*new_path);
		*new_path = NULL;
		return (ft_perror(*new_path, ": No such file or directory", 1));
	}
	free(*new_path);
	*new_path = getcwd(NULL, 1000);
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}

int	ft_chdir(char **args, char **env, char **new_path, char **old_path)
{
	if (!*(args + 1))
	{
		*new_path = ft_getenv_exec(env, "HOME");
		if (!*new_path)
			return (ft_perror(*args, ": HOME not set", 1));
	}
	else
		*new_path = ft_strdup(args[1]);
	return (chdir_help2(env, old_path, new_path));
}

int	ft_cd(char **args, char ***env)
{
	char	*new_path;
	char	*old_path;
	char	**arr;
	int		ret;

	new_path = NULL;
	old_path = NULL;
	ret = ft_chdir(args, *env, &new_path, &old_path);
	if (!ret)
	{
		arr = (char **)malloc(sizeof(char *) * 4);
		arr[0] = ft_strdup("");
		arr[1] = ft_strjoin("OLDPWD=", old_path);
		arr[2] = ft_strjoin("PWD=", new_path);
		arr[3] = NULL;
		ft_export(arr, env, 1);
		split_free(arr);
	}
	if (new_path)
		free(new_path);
	free(old_path);
	return (ret);
}
