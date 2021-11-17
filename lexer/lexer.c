/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdolilah <alhamdolilah@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:21:03 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/16 15:22:51 by alhamdolila      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*collect_exit(t_lexer *lexer)
{
	char	*str;

	str = ft_itoa(g_exit_status);
	if (!str)
		raise_error(errno);
	lexer_advance(lexer);
	return (str);
}

char	*ft_depannage(char *environement_var,
		t_lexer *lexer, int size, char **str)
{
	char	*tmp;

	if ((environement_var[0] == ' ' || environement_var[0] == '\t')
		&& size > 0 && lexer->current_char != '|'
		&& lexer->current_char != '>' && lexer->current_char != '<'
		&& lexer->current_char != '\0' && lexer->current_char != ' '
		&& lexer->current_char != '\t')
	{
		free(*str);
		tmp = *str;
		*str = ft_strdup("");
		if (!(*str))
			raise_error(errno);
		free(tmp);
	}
	free(environement_var);
	return (*str);
}

char	*get_dollar_info(t_lexer *lexer, int size)
{
	char	*environement_var;
	char	*str;
	size_t	number_ofwords;

	environement_var = ft_strdup("");
	if (!environement_var)
		raise_error(errno);
	lexer_collect_environement(lexer, &environement_var);
	str = ft_strdup("");
	if (!str)
		raise_error(errno);
	number_ofwords = ft_wordnumber(environement_var);
	if (number_ofwords == 0)
		return (ft_depannage(environement_var, lexer, size, &str));
	if ((environement_var[0] == ' ' || environement_var[0] == '\t') && size > 0)
	{
		free(str);
		str = ft_strdup(" ");
		if (!str)
			raise_error(errno);
	}
	return (lexer_split_words(lexer, environement_var, str, number_ofwords));
}

char	*lexer_collect_normalchars(t_lexer *lexer)
{
	int		begin;
	int		end;
	char	*ret_value;

	begin = lexer->current_index;
	while (lexer->current_char != '|' && lexer->current_char != '>'
		&& lexer->current_char != '<'
		&& lexer->current_char != '\0' && lexer->current_char != ' '
		&& lexer->current_char != '\t' && lexer->current_char != '$'
		&& lexer->current_char != '\'' && lexer->current_char != '"')
		lexer_advance(lexer);
	end = lexer->current_index;
	ret_value = ft_substr(lexer->line, begin, end - begin);
	if (!ret_value)
		raise_error(errno);
	return (ret_value);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*ret_value;
	char	*tmp;

	ret_value = ft_strdup("");
	while (lexer->current_char != '|' && lexer->current_char != '>'
		&& lexer->current_char != '<' && lexer->current_char != '\0'
		&& lexer->current_char != ' ' && lexer->current_char != '\t')
	{
		if (lexer->current_char == '"')
			tmp = lexer_collect_doublequotes(lexer);
		else if (lexer->current_char == '\'')
			tmp = lexer_collect_uniquotes(lexer);
		else if (lexer->current_char == '$')
			tmp = get_dollar_info(lexer, ft_strlen(ret_value));
		else
			tmp = lexer_collect_normalchars(lexer);
		append_word(&ret_value, tmp);
	}
	return (init_token(WORD_TOKEN, ret_value));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->current_char != '\0')
	{
		lexer_skype_white_spaces(lexer);
		if (lexer->current_char == '|')
			return (lexer_advance_with_token(lexer,
					init_token(PIPE_TOKEN, ft_strdup("|"))));
		if (lexer->current_char == '>')
			return (lexer_collect_append(lexer));
		if (lexer->current_char == '<')
			return (lexer_collect_here_doc(lexer));
		if (lexer->current_char != '\0')
			return (lexer_collect_id(lexer));
	}
	return (init_token(ENDOFFILE_TOKEN, ft_strdup("EOF")));
}
