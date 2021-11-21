/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:17:51 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 16:34:51 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char	*ft_oneofthose(char *str)
{
	if (str == NULL)
	{
		str = ft_strdup("");
		if (!str)
			raise_error(errno);
	}
	else
	{
		str = ft_strdup(str);
		if (!str)
			raise_error(errno);
	}
	return (str);
}

int	ft_oneofthose2(size_t number_ofwords,
	char *environement_var, t_lexer *lexer, int i)
{
	if (number_ofwords > 0
		|| ((environement_var[i] == ' ' || environement_var[i] == '\t')
			&& lexer->current_char != '|' && lexer->current_char != '>'
			&& lexer->current_char != '<' && lexer->current_char != '\0'
			&& lexer->current_char != '\t'))
	{
		return (1);
	}
	else
		return (0);
}

char	*collect_exit(t_lexer *lexer)
{
	char	*str;

	str = ft_itoa(g_exit_status);
	if (!str)
		raise_error(errno);
	lexer_advance(lexer);
	return (str);
}
