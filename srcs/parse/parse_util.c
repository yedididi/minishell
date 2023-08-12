/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:21:14 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 11:21:48 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

char	*ft_strndup(char *src, int len)
{
	char	*result;
	int		i;

	result = malloc(len);
	i = 0;
	while (i < len)
	{
		result[i] = src[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}