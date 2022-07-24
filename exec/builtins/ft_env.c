/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:17 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:30:13 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (*(args + 1) != NULL)
	{
		ft_perror(*(args + 1), ": No such file or directory", 127);
		exit(g_var.ex_sts);
	}
	else
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				ft_putendl_fd(env[i], 1);
			i++;
		}
	}
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}
