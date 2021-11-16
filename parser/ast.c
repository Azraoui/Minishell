/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:18:59 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/07 17:12:02 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*head;

	head = (t_ast *)malloc(sizeof(t_ast));
	if (!head)
		return (NULL);
	head->type = type;
	head->nodes = (void *)0;
	head->nodes_size = 0;
	head->arguments = (void *)0;
	head->arguments_size = 0;
	head->redirections = 0;
	head->redirections_size = 0;
	return (head);
}
