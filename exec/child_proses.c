
#include "../includes/exec.h"

int		ft_execve(char **args, char **env)
{
	char	**sp_env;
	char	*path;
	int		i;

	sp_env = ft_split(ft_getenv_exec(env, "PATH"), ':');
	if (!sp_env)
		return (-1);
	i = 0;
	while ((ft_lstat(args[0]) != -1) && sp_env[i])
	{
		path = ft_strjoin(ft_strjoin(sp_env[i], "/"), args[0]);
		if (ft_lstat(path))
		{
			*args = path;
			break ;
		}
		free(path);
		i++;
	}
	split_free(sp_env);
	return (execve(args[0], args, env));
}

pid_t	child_proses(t_ast *head, char ***env, t_pipe *p_pipe, t_stack **stck_pid)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		pid = getpid();
		usleep(100);
		if (check_redirections(head, &(p_pipe->last_fd), &(p_pipe->fd[1]), *env))
			exit(1);
		dup2(p_pipe->last_fd, 0);
		if (p_pipe->pipe_size < head->nodes_size || head->mode_active)
			dup2(p_pipe->fd[1], 1);
		close(p_pipe->fd[0]);
		close(p_pipe->fd[1]);
		if (!is_builtins(head->arguments, env, head))
			ft_execve(head->arguments, *env);
		exit(1);
	}
	push_stack(pid, stck_pid);
	close(p_pipe->fd[1]);
	if (stack_size(*stck_pid) == head->nodes_size)
		while (stack_size(*stck_pid))
			waitpid(pop_stack(stck_pid), NULL, 0);
	return (pid);
}
