/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:10:41 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/16 13:05:31 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	j;

	j = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	i = dest_len;
	while (src[j] && ((dstsize - dest_len - 1) > j))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dest_len + src_len);
}
