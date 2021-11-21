/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:53:52 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 01:36:27 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	len_of_node(t_node *env)
{
	int	len;

	len = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

void	free_node(t_node **head)
{
	t_node	*tmp;

	while (*head)
	{
		tmp = (*head);
		(*head) = (*head)->next;
		free(tmp->data);
		free(tmp);
	}
}

t_node	*init_node(char *data)
{
	t_node	*n;

	n = (t_node *)malloc(sizeof(t_node));
	n->data = ft_strdup(data);
	n->next = NULL;
	return (n);
}

void	push_to_node(char *data, t_node **node)
{
	t_node	*s;

	s = init_node(data);
	s->next = *node;
	*node = s;
}

t_node	*array_to_node(char **arr)
{
	int		len;
	t_node	*node;
	int		i;

	node = NULL;
	len = ppter_len(arr);
	i = len - 1;
	while (i >= 0)
		push_to_node(arr[i--], &node);
	return (node);
}
