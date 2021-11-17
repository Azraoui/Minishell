
#include "../includes/exec.h"

int	cmd_without_fork(char *cmd)
{
	if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "CD"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	is_builtins(char **arg, char ***env, t_ast *head)
{
	int	fd;

	fd = 1;
	if (head->nodes_size == 1 && cmd_without_fork(arg[0]))
		if (check_redirections(head, &fd, &fd, *env))
			return (1);
	if (!ft_strcmp(arg[0], "pwd") || !ft_strcmp(arg[0], "PWD"))
		return (ft_pwd());
	else if (!ft_strcmp(arg[0], "echo") || !ft_strcmp(arg[0], "ECHO"))
		return (ft_echo(arg));
	else if (!ft_strcmp(arg[0], "cd") || !ft_strcmp(arg[0], "CD"))
		return (ft_cd(arg, env));
	else if (!ft_strcmp(arg[0], "export"))
		return (ft_export(arg, env, fd));
	else if (!ft_strcmp(arg[0], "env") || !ft_strcmp(arg[0], "ENV"))
		return (ft_env(arg, *env));
	else if (!ft_strcmp(arg[0], "unset"))
		return (ft_unset(arg, env));
	else if (!ft_strcmp(arg[0], "exit"))
		return (ft_exit(arg));
	return (0);
}

int	ft_traitment(t_ast *head, char ***env, t_pipe *p_pipe)
{
	pid_t	p_id;
	t_stack	*stck_pid;
	t_stack	*stck_fd;
	int		i;

	stck_pid = NULL;
	stck_fd = NULL;
	if (head->nodes_size == 1 && cmd_without_fork(head->nodes[0]->arguments[0]))
		return (!is_builtins(head->nodes[0]->arguments, env, head->nodes[0]));
	i = 0;
	while (i < head->nodes_size)
	{
		head->nodes[i]->mode_active = 0;
		pipe(p_pipe->fd);
		p_pipe->pipe_size += 1;
		p_id = child_proses(head->nodes[i], env, p_pipe);
		p_pipe->last_fd = p_pipe->fd[0];
		push_stack(p_id, &stck_pid);
		push_stack(p_pipe->fd[0], &stck_fd);
		if (p_pipe->pipe_size == head->nodes_size)
			while(stack_size(stck_pid))
			{
				close(pop_stack(&stck_fd));
				waitpid(pop_stack(&stck_pid), NULL, 0);
			}	
		i++;
	}
	return (0);
}

void	exec_main(t_ast *head, char ***env)
{
	t_pipe	*link_proses;

	link_proses = (t_pipe *)malloc(sizeof(t_pipe));
	if (!head || !link_proses)
		return ;
	link_proses->last_fd = 0;
	link_proses->pipe_size = 0;
	ft_traitment(head, env, link_proses);
	free(link_proses);
}
