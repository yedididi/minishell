/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:28:33 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/13 16:17:12 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	error_input(void)
{
	//일단 여러 개의 그룹을 다 프리해준다.
	//열린 프로세스들도 kill로 다 죽여준다.
	//후에 start_shell 함수 안에 있는 while문으로 돌아가게 해준다
	
}

int	str_find_chr(char *str, char c)
{
	int i;

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
		if (*str == '_' || ft_isalpha(*str) == 1)
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
