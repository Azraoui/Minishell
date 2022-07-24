/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:18:59 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/21 22:24:37 by ael-azra         ###   ########.fr       */
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
