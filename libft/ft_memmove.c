/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:10:13 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/17 10:28:04 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*str_dst;
	const unsigned char	*str_src;

	str_dst = (unsigned char *)dst;
	str_src = (const unsigned char *)src;
	if (dst > src)
	{
		str_src = str_src + len;
		str_dst = str_dst + len;
		while (len--)
			*--str_dst = *--str_src;
	}
	else if (str_dst != str_src)
	{
		while (len--)
			*str_dst++ = *str_src++;
	}
	return (dst);
}
