/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdolilah <alhamdolilah@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:51:54 by ytaousi           #+#    #+#             */
/*   Updated: 2021/11/05 19:03:05 by alhamdolila      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char		*a;
	const unsigned char		*b;
	size_t					r;
	size_t					i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	i = 0;
	r = 0;
	while ((a[i] == b[i] && a[i] != '\0'))
		i++;
	r = a[i] - b[i];
	return (r);
}
