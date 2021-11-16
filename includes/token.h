/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:33:59 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/07 18:34:03 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	WORD_TOKEN,
	PIPE_TOKEN,
	OUTPUT_TOKEN,
	APPEND_TOKEN,
	INPUT_TOKEN,
	HERE_DOC_TOKEN,
	ENDOFFILE_TOKEN
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}					t_token;

t_token	*init_token(t_token_type type, char *content);
#endif
