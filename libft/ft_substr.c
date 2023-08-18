/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:07:04 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/22 14:39:22 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	sub_len(char const *s, unsigned int start, size_t len)
{
	long long	i;

	i = 0;
	if (ft_strlen(s) < start)
		return (-1);
	if ((s == 0) || (len == 0))
		return (-1);
	while (s[start + i] && len)
	{
		len--;
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub_str;
	size_t		i;
	long long	tmp;

	i = 0;
	tmp = sub_len(s, start, len);
	if (tmp == -1)
		return (ft_strdup(""));
	sub_str = (char *)malloc(sizeof(char) * (tmp + 1));
	if (sub_str == 0)
		return (0);
	while (tmp--)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
