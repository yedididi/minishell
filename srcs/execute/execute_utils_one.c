/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:28:33 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 17:37:31 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	str_find_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}

int	is_alpha_and_(char *str)
{
	while (*str)
	{
		if (*str == '_' || ft_isalpha(*str) == 1 || ft_isdigit(*str) == 1)
			str++;
		else
			return (0);
	}
	return (1);
}

int	chk_equal_sign(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int	ft_isspecial(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (1);
		str++;
	}
	return (0);
}
