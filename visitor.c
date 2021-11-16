/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:20:05 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/09 17:21:07 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	print_redirections(t_redir *node)
{
	printf("REDIRECTION (%s, %d)\n", node->file_name, node->type);
}

void	print_arguments(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->redirections_size)
	{
		print_redirections(node->redirections[i]);
		i++;
	}
	i = 0;
	while (i < node->arguments_size)
	{
		printf("ARGUMENT (%d) : (%s)\n", i + 1, node->arguments[i]);
		i++;
	}
}

void	print_pipeline(t_ast *node)
{
	int		i;

	i = 0;
	while (i < node->nodes_size)
	{
		printf("---------node------\n");
		print_arguments(node->nodes[i]);
		i++;
	}
}

int	print_them(t_ast *node)
{
	if (node != NULL && node->type == PIPELINE)
		print_pipeline(node);
	return (0);
}
