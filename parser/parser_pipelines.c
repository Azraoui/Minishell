/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:26:32 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 10:27:40 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_ast	*fill_pipe_size_of_all_nodes(t_ast *head)
{
	int	i;

	i = 0;
	if (!head)
		return (NULL);
	while (i < head->nodes_size)
	{
		head->nodes[i]->nodes_size = head->nodes_size;
		i++;
	}
	return (head);
}

t_ast	*parser_parse_pipelines(t_parser *parser, t_ast *head)
{
	t_ast	*node;

	while (parser->current_token->type == PIPE_TOKEN)
	{
		expected_token(parser, PIPE_TOKEN);
		node = parser_parse_normal_command(parser);
		if (!node)
			return (free_ast_pipeline(node));
		head->nodes = realloc_(head->nodes, sizeof(t_ast *), head->nodes_size);
		head->nodes_size += 1;
		head->nodes[head->nodes_size - 1] = node;
	}
	return (head);
}
