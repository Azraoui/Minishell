/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:05:19 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 04:51:24 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (check_redirections(head, &fd, &fd))
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
	return (-1);
}

void	norm_help_traitment1(t_ast *head, char ***env,
		t_pipe *p_pipe, t_stack **stck)
{
	pid_t	p_id;
	int		i;

	i = 0;
	while (i < head->nodes_size)
	{
		head->nodes[i]->mode_active = 0;
		pipe(p_pipe->fd);
		p_pipe->pipe_size += 1;
		p_id = child_proses(head->nodes[i], env, p_pipe);
		p_pipe->last_fd = p_pipe->fd[0];
		push_stack(p_id, &stck[0]);
		push_stack(p_pipe->fd[0], &stck[1]);
		if (p_pipe->pipe_size == head->nodes_size)
		{
			close(pop_stack(&stck[1]));
			norm_help_traitment2(&stck[0], &stck[1]);
		}
		i++;
	}
}

int	ft_traitment(t_ast *head, char ***env, t_pipe *p_pipe)
{
	t_stack	**stck;

	heredoc_managment(&head, *env);
	if (head->nodes_size == 1 && cmd_without_fork(head->nodes[0]->arguments[0]))
	{
		if (is_builtins(head->nodes[0]->arguments, env, head->nodes[0]) != -1)
			return (g_var.ex_sts);
	}
	else
	{
		stck = (t_stack **)malloc(sizeof(t_stack *) * 2);
		stck[0] = NULL;
		stck[1] = NULL;
		norm_help_traitment1(head, env, p_pipe, stck);
		g_var.child_id = 0;
		free(stck);
	}
	return (g_var.ex_sts);
}

void	exec_main(t_ast *head, t_node **envs)
{
	t_pipe	*link_proses;
	char	**env;
	int		exit_st;

	if (!head || !envs)
	{
		g_var.ex_sts = 258;
		return ;
	}
	skip_empty_arg(&head);
	env = node_to_array(*envs);
	free_node(envs);
	link_proses = (t_pipe *)malloc(sizeof(t_pipe));
	if (!link_proses)
		return ;
	link_proses->last_fd = 0;
	link_proses->pipe_size = 0;
	exit_st = ft_traitment(head, &env, link_proses);
	if (WIFEXITED(exit_st))
		g_var.ex_sts = WEXITSTATUS(g_var);
	else
		g_var.ex_sts = g_var.signal_sts;
	*envs = array_to_node(env);
	split_free(env);
	free(link_proses);
}
