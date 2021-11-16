/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:01:37 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/07 17:04:54 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	lexer_collect_normalchars_indoublequotes(t_lexer *lexer, char **value)
{
	char	*str;
	char	*tmp;
	int		begin;
	int		end;

	begin = lexer->current_index;
	while (lexer->current_char != '"' && lexer->current_char != '\0'
		&& lexer->current_char != '$')
		lexer_advance(lexer);
	end = lexer->current_index;
	if (lexer->current_char == '\0')
		return ;
	str = ft_substr(lexer->line, begin, end - begin);
	if (str == NULL)
		raise_error(errno);
	tmp = *value;
	*value = ft_strjoin(*value, str);
	if (*value == NULL)
		raise_error(errno);
	free(str);
	free(tmp);
}

char	*lexer_collect_doublequotes(t_lexer *lexer)
{
	char	*ret_value;

	lexer_advance(lexer);
	if (!is_closed_quote(lexer->line, lexer->current_index, '"'))
		return (ft_strdup("\""));
	ret_value = ft_strdup("");
	while (lexer->current_char != '"')
	{
		if (lexer->current_char == '$')
			lexer_collect_environement(lexer, &ret_value);
		else
			lexer_collect_normalchars_indoublequotes(lexer, &ret_value);
	}
	lexer_advance(lexer);
	return (ret_value);
}

char	*lexer_collect_uniquotes(t_lexer *lexer)
{
	int		begin;
	int		end;
	char	*ret_value;

	lexer_advance(lexer);
	begin = lexer->current_index;
	if (!is_closed_quote(lexer->line, lexer->current_index, '\''))
		return (ft_strdup("'"));
	while (lexer->current_char != '\'' && lexer->current_char != '\0')
		lexer_advance(lexer);
	lexer_advance(lexer);
	end = lexer->current_index - 1;
	ret_value = ft_substr(lexer->line, begin, end - begin);
	if (!ret_value)
		raise_error(errno);
	return (ret_value);
}
