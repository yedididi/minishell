/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:07:20 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/16 13:05:21 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_len;
	int		s2_len;
	char	*return_str;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	return_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (return_str == 0)
		return (0);
	while (*s1)
		return_str[i++] = *s1++;
	while (*s2)
		return_str[i++] = *s2++;
	return_str[i] = '\0';
	return (return_str);
}
