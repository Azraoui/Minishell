/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:10:33 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 16:26:31 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	find_herdoc(t_ast *head)
{
	int	i;

	i = 0;
	while (i < head->redirections_size)
	{
		if (head->redirections[i]->type == HERE_DOC_REDIR)
			return (1);
		i++;
	}
	return (0);
}

void	export_norm(char *var, int i, char ***env, char *value)
{
	if (value)
	{
		free(*(*env + i));
		*(*env + i) = ft_strdup(var);
	}
}
