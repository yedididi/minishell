/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:43:35 by boran             #+#    #+#             */
/*   Updated: 2023/08/27 17:12:22 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	ft_isspace(char ch)
{
	int	i;

	i = 0;
	if (ch == 0)
		return (1);
	while (ch != WHITESPACE[i] && WHITESPACE[i])
		++i;
	if (i < 6)
		return (1);
	return (0);
}

int	ft_issymbol(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return (0);
	else if (ch >= 'A' && ch <= 'Z')
		return (0);
	else if (ch >= '0' && ch <= '9')
		return (0);
	else if (ch == '_')
		return (0);
	else
		return (1);
}

char	*ft_strndup(char *src, int len)
{
	char	*result;
	int		i;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = src[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	if (!*str1 && !*str2)
		return (1);
	return (0);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
