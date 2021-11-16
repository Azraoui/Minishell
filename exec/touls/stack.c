/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:21:10 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/16 09:54:28 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_stack	*init_stack(pid_t data)
{
	t_stack	*s;

	s = (t_stack *)malloc(sizeof(t_stack));
	s->data = data;
	s->next = NULL;
	return (s);
}

int	is_empty(t_stack *s)
{
	return (!s);
}

void	push_stack(pid_t pid, t_stack **node)
{
	t_stack	*s;

	s = init_stack(pid);
	s->next = *node;
	*node = s;
}

int		stack_size(t_stack *node)
{
	int	len;

	len = 0;
	while (node)
	{
		node = node->next;
		len++;
	}
	return (len);
}

int	pop_stack(t_stack **node)
{
	int		data;
	t_stack	*tmp;

	if (is_empty(*node))
		return (INT_MIN);
	tmp = *node;
	data = tmp->data;
	*node = (*node)->next;
	free(tmp);
	return (data);
}
