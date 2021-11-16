/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:52:16 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 09:53:16 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	parser_check_error(t_parser *parser)
{
	if (parser->current_token->type == PIPE_TOKEN
		|| parser->current_token->type == ENDOFFILE_TOKEN)
		return (expected_token(parser, WORD_TOKEN));
	else
		return (0);
}

void	raise_error(int errornumber)
{
	char	*error;

	error = strerror(errornumber);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		raise_error(errno);
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->previous_token = NULL;
	return (parser);
}
