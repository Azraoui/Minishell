#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <limits.h>

typedef struct s_pipe
{
	int		pipe_size;
	int		last_fd;
	int		fd[2];
}				t_pipe;

typedef	struct	s_stack
{
	pid_t			data;
	struct s_stack	*next;
}				t_stack;

void	exec_main(t_ast *list_cmd, char ***env);
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
pid_t	child_proses(t_ast *head, char ***env, t_pipe *p_pipe, t_stack **stck_pid);
int		ft_lstat(char *path);
int		ft_execve(char **args, char **env);
int		is_builtins(char **arg, char ***env, t_ast *head);
int		check_redirections(t_ast *head, int *inp_fd, int *out_fd, char **env);
char	*convert_var_to_env(char *str, char **env, int fd);
int		pop_stack(t_stack **node);
void	push_stack(pid_t pid, t_stack **node);
int		is_empty(t_stack *s);
t_stack	*init_stack(pid_t data);
int		stack_size(t_stack *node);

#endif
