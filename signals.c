/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:05:10 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/22 04:30:35 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/exec.h"

int	ft_depanage(int signumber, pid_t chid)
{
	if (signumber == SIGINT)
	{
		(void)chid;
		kill(chid, SIGKILL);
		ft_putchar_fd('\n', 2);
		return (130);
	}
	if (signumber == SIGQUIT)
	{
		ft_putchar_fd('\n', 2);
		return (131);
	}
	return (0);
}

void	signal_handler(int signumber)
{
	if (g_var.child_id)
		g_var.signal_sts = ft_depanage(signumber, g_var.child_id);
	else
	{
		if (signumber == SIGINT)
		{
			g_var.ex_sts = 1;
			ft_putendl_fd("", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (signumber == SIGQUIT)
		{
			ft_putchar_fd('\r', 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
