/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_managment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:05:24 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/21 15:43:16 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	append_and_output(t_redir *redir, int *out_fd, t_ast *head)
{
	int	fd;

	if (redir->type == APPEND_REDIR)
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (1);
	if (*out_fd != 1)
		close(*out_fd);
	*out_fd = fd;
	head->mode_active = 1;
	return (0);
}

int	input_redir(char *name, int *input_fd)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_perror(name, ": No such file or directory", 1);
		return (g_exit_status);
	}
	if (*input_fd)
		close(*input_fd);
	*input_fd = fd;
	return (0);
}

int	here_doc(t_redir *redir, int *input_fd, char **env, char *fd_name)
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
	return (input_redir(fd_name, input_fd));
}

int	check_redirections(t_ast *head, int *inp_fd, int *out_fd)
{
	int		i;
	char	*fd_name;
	t_redir	**redir;

	i = 0;
	redir = head->redirections;
	while (i < head->redirections_size)
	{
		if ((redir[i]->type == OUTPUT_REDIR || redir[i]->type == APPEND_REDIR)
			&& (append_and_output(redir[i], out_fd, head)))
			return (1);
		else if (redir[i]->type == INPUT_REDIR
			&& (input_redir(redir[i]->file_name, inp_fd)))
			return (1);
		else if (redir[i]->type == HERE_DOC_REDIR)
		{
			fd_name = ft_strjoin_free("/tmp/heredocfile",
					ft_itoa(head->n_index));
			if (input_redir(fd_name, inp_fd))
				return (1);
			free(fd_name);
		}
		i++;
	}
	return (0);
}
