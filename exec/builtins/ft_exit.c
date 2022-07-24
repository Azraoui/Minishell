/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:24 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:30:19 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	find_numeric(char *s)
{
	int	i;

	i = 0;
	if (ft_strchr("+-", *s))
		s++;
	while (*s)
	{
		if (!ft_strchr("0123456789", *s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	if (!*(args + 1))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (!find_numeric(*(args + 1)))
	{
		ft_putendl_fd("exit", 1);
		ft_perror(*args, ": numeric argument required", 255);
		exit(g_var.ex_sts);
	}
	else if (ppter_len(args) == 2)
	{
		g_var.ex_sts = (unsigned char)ft_atoi(*(args + 1));
		ft_putendl_fd("exit", 1);
		exit(g_var.ex_sts);
	}
	else
	{
		ft_perror(*args, ": too many arguments", 1);
		return (g_var.ex_sts);
	}
}
