/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:02:49 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 01:47:37 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*ft_strjoin_free(char const *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (s2)
		free(s2);
	return (str);
}

void	set_index(t_ast **node)
{
	int	i;

	i = 0;
	while (i < (*node)->nodes_size)
	{
		(*node)->nodes[i]->n_index = i + 1;
		i++;
	}
}

int	here_docc(t_redir *redir, char **env, char *fd_name)
{
	int		fd;
	char	*line;

	fd = open(fd_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("heredoc :");
		g_exit_status = 1;
		return (g_exit_status);
	}
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(redir->file_name, line))
			break ;
		convert_var_to_env(line, env, fd);
		free(line);
	}
	free(line);
	if (fd)
		close(fd);
	return (0);
}

int	norm_help(char **env, char *fd_name, t_ast *head)
{
	int	i;

	i = 0;
	while (i < head->redirections_size)
	{
		if (head->redirections[i]->type == HERE_DOC_REDIR)
		{
			if (here_docc(head->redirections[i], env, fd_name))
				return (1);
		}
		i++;
	}
	return (0);
}

void	heredoc_managment(t_ast **node, char **env)
{
	t_ast	*head;
	char	*fd_name;
	int		i;
	int		pid;

	set_index(node);
	head = *node;
	pid = fork();
	if (!pid)
	{
		i = 0;
		while (i < head->nodes_size)
		{
			fd_name = ft_strjoin_free("/tmp/heredocfile",
					ft_itoa(head->nodes[i]->n_index));
			if (norm_help(env, fd_name, head->nodes[i]))
				break ;
			free(fd_name);
			i++;
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
