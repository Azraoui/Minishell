/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:03:47 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 04:50:46 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <limits.h>
# include "../get_next_line.h"

typedef struct s_pipe
{
	int		pipe_size;
	int		last_fd;
	int		fd[2];
	int		ret[2];
}				t_pipe;

typedef struct s_stack
{
	pid_t			data;
	struct s_stack	*next;
}				t_stack;

void	exec_main(t_ast *list_cmd, t_node **envs);
int		ft_echo(char **args);
int		ft_cd(char **args, char ***env);
int		ft_pwd(void);
int		ft_export(char **args, char ***env, int fd);
int		ft_env(char **args, char **env);
int		ft_unset(char **args, char ***env);
int		ft_exit(char **args);
char	*ft_getenv_exec(char **env, char *name);
void	split_free(char **ptr);
void	sort_arr_alphab(char **env);
int		ppter_len(char **s);
int		ft_isalnum_var(int c);
pid_t	child_proses(t_ast *head, char ***env, t_pipe *p_pipe);
int		ft_lstat(char *path, int status);
int		ft_execve(char **args, char **env);
int		is_builtins(char **arg, char ***env, t_ast *head);
int		check_redirections(t_ast *head, int *inp_fd, int *out_fd);
void	convert_var_to_env(char *str, char **env, int fd);
int		pop_stack(t_stack **node);
void	push_stack(pid_t pid, t_stack **node);
int		is_empty(t_stack *s);
t_stack	*init_stack(pid_t data);
int		stack_size(t_stack *node);
int		ft_perror(char *cmd, char *message, int error);
char	**node_to_array(t_node *env);
int		len_of_node(t_node *env);
void	free_node(t_node **head);
t_node	*array_to_node(char **arr);
int		find_herdoc(t_ast *head);
void	heredoc_managment(t_ast **head, char **env);
int		here_doc(t_redir *redir, int *input_fd, char **env, char *fd_name);
char	*ft_strjoin_free(char const *s1, char *s2);
void	export_norm(char *var, int i, char ***env, char *value);
void	skip_empty_arg(t_ast **head);
void	norm_help_traitment2(t_stack **stack_1, t_stack **stack_2);

#endif
