/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:12:16 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/07 18:47:40 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	add_single_or_double_q_to_value(char **value, char c)
{
	char	*tmp;

	tmp = ft_strjoinchar(*value, "", c);
	if (tmp == NULL)
		raise_error(errno);
	free(*value);
	*value = tmp;
	return ;
}

void	collect_single_double_quotes(t_lexer *lexer, int *index,
													char **value, int *flag)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;
	char	c;

	c = lexer->line[*index];
	index_i = ++(*index);
	if (!is_closed_quote(lexer->line, index_i, c))
		return (add_single_or_double_q_to_value(value, c));
	while (lexer->line[*index] != c)
		(*index)++;
	index_f = *index;
	*index += 1;
	str = ft_substr(lexer->line, index_i, index_f - index_i);
	if (str == NULL)
		raise_error(errno);
	tmp = ft_strjoin(*value, str);
	if (tmp == NULL)
		raise_error(errno);
	free(*value);
	free(str);
	*value = tmp;
	*flag = 1;
}

void	collect_simple_chars(t_lexer *lexer, int *index, char **value)
{
	char	*str;
	char	*tmp;
	int		index_i;
	int		index_f;

	index_i = *index;
	while (lexer->line[*index] != '|' && lexer->line[*index] != '>'
		&& lexer->line[*index] != '<' && lexer->line[*index] != '\0'
		&& lexer->line[*index] != ' ' && lexer->line[*index] != 11
		&& lexer->line[*index] != '"'
		&& lexer->line[*index] != '\'')
		(*index)++;
	index_f = *index;
	str = ft_substr(lexer->line, index_i, index_f - index_i);
	if (str == NULL)
		raise_error(errno);
	tmp = ft_strjoin(*value, str);
	if (tmp == NULL)
		raise_error(errno);
	free(*value);
	free(str);
	*value = tmp;
}

void	skip_whitespaces(char *cmd_line, int *index)
{
	while (cmd_line[*index] == ' ' || cmd_line[*index] == '\t')
		(*index)++;
}

void	debug_here_document(t_parser *parser, t_redir_type *type, int index)
{
	char	*value;
	int		flag;

	if (type)
		;
	flag = 0;
	value = ft_strdup("");
	skip_whitespaces(parser->lexer->line, &index);
	while (parser->lexer->line[index] != '|'
		&& parser->lexer->line[index] != '>'
		&& parser->lexer->line[index] != '<'
		&& parser->lexer->line[index] != '\0'
		&& parser->lexer->line[index] != ' '
		&& parser->lexer->line[index] != 11)
	{
		if (parser->lexer->line[index] == '"'
			|| parser->lexer->line[index] == '\'')
			collect_single_double_quotes(parser->lexer, &index, &value, &flag);
		else
			collect_simple_chars(parser->lexer, &index, &value);
	}
	free(parser->previous_token->content);
	parser->previous_token->content = value;
}
