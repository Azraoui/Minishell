/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:17 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 12:45:35 by ael-azra         ###   ########.fr       */
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
		exit(g_exit_status);
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
	g_exit_status = 0;
	return (g_exit_status);
}
