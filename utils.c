/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:06:35 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 09:41:43 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

t_node	*append(int n, char *data, t_node *head)
{
	t_node	*temp;
	t_node	*temp1;
	int		i;

	temp = malloc(sizeof(t_node));
	temp->data = ft_strdup(data);
	temp->next = NULL;
	if (n == 1)
	{
		temp->next = head;
		head = temp;
		return (head);
	}
	temp1 = head;
	i = -1;
	while (temp1->next != NULL)
		temp1 = temp1->next;
	temp1->next = temp;
	return (head);
}

t_node	*ft_tab2lst(t_node *head, char **env)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	while (env[++i] != NULL)
	{
		head = append(a, env[i], head);
		++a;
	}
	return (head);
}

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstappend(t_env **lst, t_env *env)
{
	t_env	*actual;
	t_env	*new;

	if (!lst)
		return ;
	actual = *lst;
	if (actual)
	{
		while (actual->next)
			actual = actual->next;
		new = ft_new_env(env->key, env->value);
		actual->next = new;
	}
	else
	{
		new = ft_new_env(env->key, env->value);
		*lst = new;
	}
}

void	append_word(char **value, char *tmp)
{
	char	*tmp2;

	tmp2 = *value;
	*value = ft_strjoin(*value, tmp);
	if (!(*value))
		raise_error(errno);
	free(tmp2);
	free(tmp);
}
