/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:09:57 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/23 11:23:35 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int					i;
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	i = 0;
	c_dst = (unsigned char *)dst;
	c_src = (const unsigned char *)src;
	if ((!dst && !src))
		return (dst);
	while (n--)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	return (dst);
}
