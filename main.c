/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:47:48 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/22 02:31:45 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"

void	launch_program(char *line, t_node **envs)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*head;

	lexer = init_lexer(line, *envs);
	parser = init_parser(lexer);
	head = parser_parse(parser);
	exec_main(head, envs);
	free_ast_pipeline(head);
	ft_free_parser(parser);
}

int	skip_space(char **line)
{
	int		i;
	char	*s;

	i = 0;
	s = *line;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
	{
		free(*line);
		return (0);
	}
	return (1);
}

int	check_error_line(char **line)
{
	if (!(*line))
	{
		printf("SIGQUIT quited from here got Y'a\n");
		exit(0);
	}
	if (!skip_space(line))
		return (0);
	if (*line[0] == '\0')
	{
		free(*line);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_node		*envs;

	if (ac || av)
		;
	envs = NULL;
	envs = ft_tab2lst(envs, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline("Minish :> ");
		if (check_error_line(&line) == 0)
			continue ;
		add_history(line);
		launch_program(line, &envs);
		free(line);
	}
	return (0);
}
