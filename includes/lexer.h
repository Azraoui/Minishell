/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdolilah <alhamdolilah@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:36:43 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/16 15:21:54 by alhamdolila      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/stat.h>
# include "token.h"
# include "ast.h"

int	g_exit_status;

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}				t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_lexer
{
	int			current_index;
	char		current_char;
	char		*line;
	t_node		*environement;
}				t_lexer;

t_lexer		*init_lexer(char *line, t_node *environement);
t_token		*lexer_get_next_token(t_lexer *lexer);
t_token		*lexer_collect_id(t_lexer *lexer);
char		*lexer_collect_uniquotes(t_lexer *lexer);
char		*lexer_collect_normalchars(t_lexer *lexer);
char		*lexer_collect_doublequotes(t_lexer *lexer);
void		lexer_collect_environement(t_lexer *lexer, char **ret_value);
char		*get_dollar_info(t_lexer *lexer, int size);
char		*collect_exit(t_lexer *lexer);
char		*collect_environement(t_lexer *lexer);
char		*ft_getenv(char *name, t_node *head);
char		*get_next_word(char *env, int *index);
void		lexer_advance(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, t_token *token);
void		lexer_skype_white_spaces(t_lexer *lexer);
void		append_word(char **value, char *tmp);
int			is_closed_quote(char *line, int index, char quote);
t_node		*ft_tab2lst(t_node *head, char *envp[]);
void		ft_lstappend(t_env **lst, t_env *env);
t_env		*ft_new_env(char *key, char *value);
char		*ft_get_value(char *env);
char		*ft_get_key(char *env);
void		signal_handler(int signumber);
char		*lexer_split_words(t_lexer *lexer,
				char *environement_var, char *str, size_t number_ofwords);
#endif 
