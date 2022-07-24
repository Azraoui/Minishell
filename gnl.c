/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 18:15:13 by ael-azra          #+#    #+#             */
/*   Updated: 2021/11/22 00:20:38 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ret(int i, char **buff)
{
	free(*buff);
	if (i != 0)
		return (1);
	return (0);
}

int	gnl(int fd, char **line)
{
	char	*buff;
	char	*ptr;
	int		i;

	ptr = NULL;
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	*line = ft_strdup("");
	i = read(fd, buff, BUFFER_SIZE);
	while (!ptr && i)
	{
		buff[i] = '\0';
		ptr = ft_strchr(buff, '\n');
		if (ptr)
		{
			*ptr = '\0';
			ptr++;
		}
		*line = ft_strjoin(*line, buff);
		if (!ptr)
			i = read(fd, buff, BUFFER_SIZE);
	}
	return (ret(i, &buff));
}
