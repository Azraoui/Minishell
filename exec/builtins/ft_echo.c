/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:12 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 04:05:17 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	skipn(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	skip_argof_n(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (!(!ft_strncmp(args[i], "-n", 2) && skipn(args[i])))
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(char **args)
{
	int		i;

	g_var.ex_sts = 0;
	if ((*(args + 1)) && !ft_strncmp(args[1], "-n", 2) && skipn(args[1]))
	{
		i = skip_argof_n(args);
		while (args[i])
		{
			ft_putstr_fd(args[i++], 1);
			if (args[i])
				ft_putchar_fd(' ', 1);
		}
		return (g_var.ex_sts);
	}
	i = 1;
	while ((*(args + 1)) && args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (g_var.ex_sts);
}
