/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_var_to_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:48 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 01:31:48 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*getenv_var(char *str, int *index, char **env)
{
	int		i;
	int		start;
	char	*sbustr;
	char	*ret;

	start = *index;
	i = (*index);
	if (str[++i] == '?')
	{
		i++;
		*index = i;
		return (ft_itoa(0));
	}
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i])
			|| ft_isdigit(str[i++])))
	*index = i;
	if ((start + 1) < i)
	{
		sbustr = ft_substr(str + 1, start, i - (start + 1));
		ret = ft_getenv_exec(env, sbustr);
		if (sbustr)
			free(sbustr);
		return (ret);
	}
	return (ft_substr(str, start, 1));
}

void	convert_var_to_env(char *str, char **env, int fd)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			s = getenv_var(str + i, &i, env);
			ft_putstr_fd(s, fd);
			free(s);
			break ;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}
