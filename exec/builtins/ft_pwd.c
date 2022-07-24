/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:04:35 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:30:26 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_pwd(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 1000);
	if (!path)
		exit(1);
	if (getcwd(path, 1000))
		ft_putendl_fd(path, 1);
	else
		perror("");
	free(path);
	g_var.ex_sts = 0;
	return (g_var.ex_sts);
}
