/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_environement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:39:13 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/21 16:36:06 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*get_next_word(char *env, int *index)
{
	char	*word;
	int		index_i;
	int		index_f;

	*index = 0;
	while (env[*index] == ' ' || env[*index] == '\t')
		*index += 1;
	index_i = *index;
	while (env[*index] != ' ' && env[*index] != '\t' && env[*index] != '\0')
		*index += 1;
	index_f = *index;
	word = ft_substr(env, index_i, index_f - index_i);
	if (word == NULL)
		raise_error(errno);
	return (word);
}

char	*lexer_split_words(t_lexer *lexer,
		char *environement_var, char *str, size_t number_ofwords)
{
	char	*word;
	char	*tmp;
	int		i;

	while (number_ofwords-- > 0)
	{
		word = get_next_word(environement_var, &i);
		tmp = str;
		if (ft_oneofthose2(number_ofwords, environement_var, lexer, i) == 1)
		{
			str = ft_strjoinchar(str, word, ' ');
			if (!str)
				raise_error(errno);
		}
		else
		{
			str = ft_strjoin(str, word);
			if (!str)
				raise_error(errno);
		}
		free(tmp);
		free(word);
	}
	free(environement_var);
	return (str);
}

char	*ft_getenv(char *name, t_node *head)
{
	t_node	*current;
	char	**dst;
	char	*value;

	if (head == NULL)
		return (NULL);
	current = head;
	while (1)
	{
		dst = ft_split(current->data, '=');
		if (ft_strcmp(dst[0], name) == 0)
			break ;
		free(dst[0]);
		free(dst[1]);
		free(dst);
		current = current->next;
		if (current == NULL)
			return (NULL);
	}
	value = dst[1];
	free(dst[0]);
	free(dst);
	return (value);
}

char	*collect_environement(t_lexer *lexer)
{
	char	*tmp2;
	char	*str;
	int		start;
	int		end;

	start = lexer->current_index;
	while (lexer->current_char == '_' || ft_isalnum(lexer->current_char))
		lexer_advance(lexer);
	end = lexer->current_index;
	str = ft_substr(lexer->line, start, end - start);
	if (str == NULL)
		raise_error(errno);
	tmp2 = str;
	str = ft_getenv(str, lexer->environement);
	free(tmp2);
	tmp2 = str;
	str = ft_oneofthose(str);
	free(tmp2);
	return (str);
}

void	lexer_collect_environement(t_lexer *lexer, char **ret_value)
{
	char	*tmp;
	char	*tmp2;

	lexer_advance(lexer);
	if (lexer->current_char == '"')
		tmp = ft_substr(lexer->line, lexer->current_index - 1, 1);
	else if (lexer->current_char == '?')
	{
		tmp = collect_exit(lexer);
	}
	else if (lexer->current_char != '_' && !ft_isalpha(lexer->current_char))
	{
		tmp = ft_substr(lexer->line, lexer->current_index - 1, 2);
		if (!tmp)
			raise_error(errno);
		lexer_advance(lexer);
	}
	else
		tmp = collect_environement(lexer);
	tmp2 = *ret_value;
	*ret_value = ft_strjoin(*ret_value, tmp);
	if (*ret_value == NULL)
		raise_error(errno);
	free(tmp);
	free(tmp2);
}
