/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:12:45 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/23 10:30:31 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*tmp;

	tmp = (const unsigned char *)s;
	i = 0;
	while (n > i)
	{
		if (tmp[i] == (unsigned char)c)
			return ((void *)(&tmp[i]));
		i++;
	}
	return (0);
}
