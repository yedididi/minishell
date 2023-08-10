/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:13:07 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/23 10:40:49 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;
	int	n_len;
	int	len_tmp;

	i = 0;
	n_len = 0;
	while (needle[n_len])
		n_len++;
	if (n_len == 0)
		return ((char *)haystack);
	while (haystack[i] && len)
	{
		j = 0;
		len_tmp = len;
		while ((haystack[i + j] == needle[j]) && len_tmp--)
		{
			if (j + 1 == n_len)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
		len--;
	}
	return (0);
}
