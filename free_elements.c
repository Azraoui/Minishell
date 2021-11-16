/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:47:12 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 09:48:42 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.h"

void	ft_free_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->lexer != NULL)
			free(parser->lexer);
		if (parser->current_token)
			free_token(parser->current_token);
		if (parser->previous_token)
			free_token(parser->previous_token);
		free(parser);
	}
}

t_ast	*ft_free_astnode_command(t_ast *node)
{
	if (node != NULL)
	{
		while (node->arguments_size-- > 0)
			free(node->arguments[node->arguments_size]);
		free(node->arguments);
		while (node->redirections_size-- > 0)
		{
			free(node->redirections[node->redirections_size]->file_name);
			free(node->redirections[node->redirections_size]);
		}
		free(node->redirections);
		free(node);
	}
	return (NULL);
}

t_ast	*free_ast_pipeline(t_ast *head)
{
	if (head != NULL)
	{
		while (head->nodes_size-- > 0)
			ft_free_astnode_command(head->nodes[head->nodes_size]);
		free(head->nodes);
		free(head);
	}
	return (NULL);
}

void	free_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->type != WORD_TOKEN)
			free(token->content);
		free(token);
	}
}

void	*realloc_(void *old_alloc, size_t count, size_t old_size)
{
	void	*new_allo;

	new_allo = ft_realloc(old_alloc, count * old_size, count * (old_size + 1));
	if (new_allo == NULL)
		raise_error(errno);
	return (new_allo);
}
