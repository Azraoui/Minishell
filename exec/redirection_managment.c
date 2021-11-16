
#include "../includes/exec.h"

int	append_and_output(t_redir *redir, int *out_fd, t_ast *head)
{
	int	fd;

	if (redir->type == APPEND_TOKEN)
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (1);
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
		perror("-> I. WAS HERE:");
		return (1);
	}
	*input_fd = fd;
	return (0);
}

int	here_doc(t_redir *redir, int *input_fd, char **env)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredocfile", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("heredoc :");
		return (1);
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
	close(fd);
	return (input_redir("/tmp/heredocfile", input_fd));
}

int	check_redirections(t_ast *head, int *inp_fd, int *out_fd, char **env)
{
	int	i;

	i = 0;
	while (i < head->redirections_size)
	{
		if (head->redirections[i]->type == OUTPUT_REDIR
			 || head->redirections[i]->type == APPEND_REDIR)
		{
				if (append_and_output(head->redirections[i], out_fd, head))
					return (1);
		}
		else if (head->redirections[i]->type == INPUT_REDIR)
		{
			if (input_redir(head->redirections[i]->file_name, inp_fd))
				return (1);
		}
		else
			here_doc(head->redirections[i], inp_fd, env);
		i++;
	}
	return (0);
}