/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:05:09 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 01:36:11 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ppter_len(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
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

int	ft_lstat(char *path, int status)
{
	struct stat	buf;

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

char	**node_to_array(t_node *env)
{
	int		i;
	char	**pptr;
	int		node_len;

	node_len = len_of_node(env);
	pptr = (char **)malloc(sizeof(char *) * (node_len + 1));
	if (!pptr || !env)
		return (NULL);
	i = 0;
	while (i < node_len && env)
	{
		pptr[i++] = ft_strdup(env->data);
		env = env->next;
	}
	pptr[i] = NULL;
	return (pptr);
}
