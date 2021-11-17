/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdolilah <alhamdolilah@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:24:39 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/17 20:02:13 by alhamdolila      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	expected_token(t_parser *parser, t_token_type type)
{
	if (parser->current_token->type == type)
	{
		free_token(parser->previous_token);
		parser->previous_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
		return (0);
	}
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, parser->current_token->content,
		ft_strlen(parser->current_token->content));
	write(2, "'\n", 2);
	return (1);
}

void	parser_parse_arguments(t_parser *parser, t_ast *node)
{
	while (parser->current_token->type == WORD_TOKEN)
	{
		node->arguments = realloc_(node->arguments,
				sizeof(char *), node->arguments_size);
		node->arguments_size += 1;
		node->arguments[node->arguments_size - 1]
			= parser->current_token->content;
		expected_token(parser, WORD_TOKEN);
	}
}

t_ast	*parser_parse_normal_command(t_parser *parser)
{
	t_ast	*node;

	if (parser_check_error(parser))
		return (NULL);
	node = init_ast(COMMAND);
	while (parser->current_token->type != PIPE_TOKEN
		&& parser->current_token->type != ENDOFFILE_TOKEN)
	{
		if (parser->current_token->type == WORD_TOKEN)
			parser_parse_arguments(parser, node);
		else if (parser_parse_redirections(parser, node))
			return (ft_free_astnode_command(node));
	}
	node->arguments = realloc_(node->arguments,
			sizeof(char *), node->arguments_size);
	node->arguments[node->arguments_size] = NULL;
	return (node);
}

t_ast	*parser_parse(t_parser *parser)
{
	t_ast	*head;
	t_ast	*node;

	node = parser_parse_normal_command(parser);
	if (!node)
		return (NULL);
	head = init_ast(PIPELINE);
	head->nodes = (t_ast **)malloc(sizeof(t_ast *));
	if (!head->nodes)
		raise_error(errno);
	head->nodes[0] = node;
	head->nodes_size += 1;
	if (parser->current_token->type == PIPE_TOKEN)
		head = parser_parse_pipelines(parser, head);
	return (fill_pipe_size_of_all_nodes(head));
}
