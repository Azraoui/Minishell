/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:40:54 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/21 16:35:14 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef struct s_parser
{
	t_lexer		*lexer;
	t_token		*current_token;
	t_token		*previous_token;
}				t_parser;

t_parser		*init_parser(t_lexer *lexer);
t_ast			*parser_parse(t_parser *parser);
t_ast			*parser_parse_normal_command(t_parser *parser);
int				parser_parse_redirections(t_parser *parser, t_ast *node);
void			parser_parse_arguments(t_parser *parser, t_ast *node);
t_redir_type	check_redirection(t_parser *parser);
int				expected_token(t_parser *parser, t_token_type type);
t_ast			*fill_pipe_size_of_all_nodes(t_ast *ast);
t_ast			*parser_parse_pipelines(t_parser *parser, t_ast *head);
int				parser_check_error(t_parser *parser);
void			ft_free_parser(t_parser *parser);
void			free_token(t_token *token);
t_ast			*free_ast_pipeline(t_ast *head);
t_ast			*ft_free_astnode_command(t_ast *node);
void			raise_error(int errnum);
void			*realloc_(void *old_alloc, size_t count, size_t old_size);
void			debug_here_document(t_parser *parser,
					t_redir_type *type, int index);
void			skip_whitespaces(char *cmd_line, int *index);
void			collect_simple_chars(t_lexer *lexer, int *index, char **value);
void			collect_single_double_quotes(t_lexer *lexer,
					int *index, char **value, int *flag);
void			add_single_or_double_q_to_value(char **value, char c);
t_token			*lexer_collect_append(t_lexer *lexer);
t_token			*lexer_collect_here_doc(t_lexer *lexer);
int				print_them(t_ast *node);
void			print_pipeline(t_ast *node);
void			print_arguments(t_ast *node);
void			print_redirections(t_redir *node);
char			*ft_oneofthose(char *str);
char			*collect_exit(t_lexer *lexer);
int				ft_oneofthose2(size_t number_ofwords,
					char *environement_var, t_lexer *lexer, int i);
#endif
