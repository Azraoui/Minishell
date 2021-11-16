/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaousi <yassir.taous@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:42:02 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/08 12:59:10 by ytaousi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isupper(int c)
{
	if (c < 65 || c > 90)
		return (0);
	else
		return (1);
}

static int	ft_islower(int c)
{
	if (c < 97 || c > 122)
		return (0);
	else
		return (1);
}

int	ft_isalpha(int c)
{
	if (!ft_isupper(c) && !ft_islower(c))
		return (0);
	else
		return (1);
}
