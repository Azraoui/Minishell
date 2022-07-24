/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:05:14 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 03:31:03 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*norm_help1(char **args, char **sp_env)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (!ft_lstat(args[0], 0) && sp_env[i])
	{
		if (!args[0])
			exit(0);
		tmp = ft_strjoin(sp_env[i], "/");
		path = ft_strjoin(tmp, args[0]);
		free(tmp);
		if ((ft_lstat(args[0], 1) != -1) && ft_lstat(path, 0))
		{
			*args = path;
			break ;
		}
		free(path);
		i++;
	}
	return (sp_env[i]);
}

int	ft_execve(char **args, char **env)
{
	char	**sp_env;
	char	*tmp;

	tmp = ft_getenv_exec(env, "PATH");
	if (!tmp)
		exit(ft_perror(args[0], ": No such file or directory", 127));
	sp_env = ft_split(tmp, ':');
	if (!sp_env)
		return (1);
	free(tmp);
	if (!norm_help1(args, sp_env))
		exit(ft_perror(args[0], ": command not found", 127));
	split_free(sp_env);
	return (execve(args[0], args, env));
}

pid_t	child_proses(t_ast *head, char ***env, t_pipe *p_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (!pid)
	{
		if (check_redirections(head, &(p_pipe->last_fd), &(p_pipe->fd[1])))
			exit(1);
		dup2(p_pipe->last_fd, 0);
		if (p_pipe->pipe_size < head->nodes_size || head->mode_active)
			dup2(p_pipe->fd[1], 1);
		close(p_pipe->fd[0]);
		close(p_pipe->fd[1]);
		if (is_builtins(head->arguments, env, head) == -1)
			ft_execve(head->arguments, *env);
		exit(g_var.ex_sts);
	}
	g_var.child_id = pid;
	close(p_pipe->fd[1]);
	return (pid);
}
