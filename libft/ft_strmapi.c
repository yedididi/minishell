/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:08:04 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/23 12:17:18 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*return_str;

	i = 0;
	len = (unsigned int)ft_strlen(s);
	return_str = (char *)malloc(sizeof(char) * (len + 1));
	if (return_str == 0)
		return (0);
	while (len > i)
	{
		return_str[i] = (*f)(i, s[i]);
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
}
