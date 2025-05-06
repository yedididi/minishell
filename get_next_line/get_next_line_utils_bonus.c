/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:13:02 by yejlee2           #+#    #+#             */
/*   Updated: 2022/12/08 11:50:46 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strnndup(const char *s1, int byte)
{
	char	*dest;
	int		i;

	i = 0;
	if (byte == 0)
		return (0);
	dest = (char *)malloc(sizeof(char) * (byte + 1));
	if (dest == 0)
		return (0);
	while (s1[i] && byte)
	{
		dest[i] = s1[i];
		i++;
		byte--;
	}
	dest[i] = '\0';
	return (dest);
}
