/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdolilah <alhamdolilah@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:47:48 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/16 12:50:35 by alhamdolila      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/exec.h"

void	launch_program(char *line, t_node *envs, char ***env)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*head;

	lexer = init_lexer(line, envs);
	parser = init_parser(lexer);
	head = parser_parse(parser);
	// print_them(head);
	exec_main(head, env);
	free_ast_pipeline(head);
	ft_free_parser(parser);
}

int	check_error_line(char **line)
{
	if (!(*line))
	{
		printf("SIGQUIT quited from here got Y'a\n");
		exit(0);
	}
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

	if (ac || av || envp)
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
		launch_program(line, envs, &envp);
		free(line);
	}
	return (0);
}
