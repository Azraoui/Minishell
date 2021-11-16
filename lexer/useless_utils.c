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

int ft_oneofthose2(size_t number_ofwords, char *environement_var, t_lexer *lexer, int i)
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