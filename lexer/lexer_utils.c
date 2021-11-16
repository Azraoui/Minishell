/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:00:10 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 10:37:04 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_lexer	*init_lexer(char *line, t_node *environement)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->line = line;
	lexer->current_index = 0;
	lexer->current_char = lexer->line[lexer->current_index];
	lexer->environement = environement;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->current_char != '\0')
	{
		lexer->current_index += 1;
		lexer->current_char = lexer->line[lexer->current_index];
	}
}

void	lexer_skype_white_spaces(t_lexer *lexer)
{
	while (lexer->current_char == ' ' || lexer->current_char == 11)
		lexer_advance(lexer);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

int	is_closed_quote(char *line, int index, char quote)
{
	int	i;

	i = index;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			return (1);
		i++;
	}
	return (0);
}
