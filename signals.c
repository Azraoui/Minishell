/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:05:10 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/21 16:10:03 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

void	signal_handler(int signumber)
{
	if (signumber == SIGINT)
	{
		ft_putendl_fd("", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signumber == SIGQUIT)
	{
		ft_putchar_fd('\r', 2);
		rl_on_new_line();
		rl_redisplay();
	}
}
