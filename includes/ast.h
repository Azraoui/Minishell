/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:34:40 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/20 23:09:13 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_redir_type
{
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND_REDIR,
	HERE_DOC_REDIR
}				t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file_name;
}				t_redir;

typedef enum e_ast_type
{
	PIPELINE,
	COMMAND
}					t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	**nodes;
	int				nodes_size;
	char			**arguments;
	int				arguments_size;
	t_redir			**redirections;
	int				redirections_size;
	int				mode_active;
	int				n_index;
}				t_ast;

t_ast	*init_ast(t_ast_type type);
#endif
