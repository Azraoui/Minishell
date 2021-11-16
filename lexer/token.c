/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:00:35 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/07 17:01:25 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_token	*init_token(t_token_type type, char *content)
{
	t_token	*token;

	if (!content)
		raise_error(errno);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		raise_error(errno);
	token->type = type;
	token->content = content;
	return (token);
}
