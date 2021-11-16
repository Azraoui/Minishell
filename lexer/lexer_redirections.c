/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:44:57 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 13:46:07 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_token	*lexer_collect_append(t_lexer *lexer)
{
	if (lexer->line[lexer->current_index + 1] == '>')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer,
				init_token(APPEND_TOKEN, ft_strdup(">>"))));
	}
	else
		return (lexer_advance_with_token(lexer,
				init_token(OUTPUT_TOKEN, ft_strdup(">"))));
}

t_token	*lexer_collect_here_doc(t_lexer *lexer)
{
	if (lexer->line[lexer->current_index + 1] == '<')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer,
				init_token(HERE_DOC_TOKEN, ft_strdup("<<"))));
	}
	else
		return (lexer_advance_with_token(lexer,
				init_token(INPUT_TOKEN, ft_strdup("<"))));
}
