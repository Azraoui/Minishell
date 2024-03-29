/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:57 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:31:50 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_perror(char *cmd, char *message, int error)
{
	ft_putstr_fd("Minish: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
	g_var.ex_sts = error;
	return (error);
}
