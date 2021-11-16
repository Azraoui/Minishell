/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:29:18 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 10:29:59 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_redir_type	check_redirection(t_parser *parser)
{
	t_redir_type	type;

	if (parser->current_token->type == OUTPUT_TOKEN)
		type = OUTPUT_REDIR;
	else if (parser->current_token->type == APPEND_TOKEN)
		type = APPEND_REDIR;
	else if (parser->current_token->type == INPUT_TOKEN)
		type = INPUT_REDIR;
	else
		type = HERE_DOC_REDIR;
	return (type);
}

int	parser_parse_redirections(t_parser *parser, t_ast *node)
{
	int				i;
	t_redir_type	type;

	type = check_redirection(parser);
	i = parser->lexer->current_index;
	expected_token(parser, parser->current_token->type);
	if (expected_token(parser, WORD_TOKEN))
		return (1);
	node->redirections = realloc_(node->redirections,
			sizeof(t_redir *), node->redirections_size);
	node->redirections_size += 1;
	node->redirections[node->redirections_size - 1]
		= (t_redir *)malloc(sizeof(t_redir));
	if (node->redirections[node->redirections_size - 1] == NULL)
		raise_error(errno);
	if (type == HERE_DOC_REDIR)
	{
		(void )type;
	}
	node->redirections[node->redirections_size - 1]->type = type;
	node->redirections[node->redirections_size - 1]->file_name
		= parser->previous_token->content;
	return (0);
}
