/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:35:39 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 15:38:58 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_double_char(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int	isnumber_str(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	over_longlong(char *str)
{
	int	len;

	if (ft_strncmp("-9223372036854775808\0", str, 21) == 0)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	len = ft_strlen(str);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		if (ft_strncmp("9223372036854775807\0", str, 20) < 0)
			return (1);
	}
	return (0);
}

long long	ft_atol(char *str)
{
	long long	num;
	long long	sign;

	num = 0;
	sign = 1;
	if (ft_strncmp("-9223372036854775808\0", str, 21) == 0)
		return (-9223372036854775807 - 1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

void	no_file_dir_err(char *str)
{
	ft_printf_err("minishell: %s: No such file or directory\n", str);
	exit(127);
}
