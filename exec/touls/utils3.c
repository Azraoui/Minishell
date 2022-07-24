/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:10:33 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 04:50:38 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	find_herdoc(t_ast *head)
{
	int	i;

	i = 0;
	while (i < head->redirections_size)
	{
		if (head->redirections[i]->type == HERE_DOC_REDIR)
			return (1);
		i++;
	}
	return (0);
}

void	export_norm(char *var, int i, char ***env, char *value)
{
	if (value || ft_strchr(var, '='))
	{
		free(*(*env + i));
		*(*env + i) = ft_strdup(var);
	}
}

char	**check_args(char **args, int *args_size)
{
	int		i;
	int		len;
	char	**cmd;
	int		j;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			len++;
		i++;
	}
	cmd = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = 0;
	while (args[++i])
	{
		if (args[i][0] != '\0')
			cmd[j++] = ft_strdup(args[i]);
	}
	*args_size = j;
	cmd[j] = NULL;
	return (cmd);
}

void	skip_empty_arg(t_ast **head)
{
	int		i;
	char	**tmp;

	i = 0;
	while (i < (*head)->nodes_size)
	{
		tmp = (*head)->nodes[i]->arguments;
		(*head)->nodes[i]->arguments = check_args((*head)->nodes[i]->arguments,
				&(*head)->nodes[i]->arguments_size);
		split_free(tmp);
		i++;
	}
}

void	norm_help_traitment2(t_stack **stack_1, t_stack **stack_2)
{
	if (WIFEXITED(g_var.ex_sts))
		waitpid(pop_stack(stack_1), &g_var.ex_sts, 0);
	else
	{
		waitpid(pop_stack(stack_1), NULL, 0);
		g_var.signal_sts = 1;
	}
	while (stack_size(*stack_1))
	{
		close(pop_stack(stack_2));
		waitpid(pop_stack(stack_1), NULL, 0);
	}
}
