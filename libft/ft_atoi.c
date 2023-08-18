/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:13:25 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/16 12:56:12 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	minus;
	int	number;

	number = 0;
	minus = 1;
	while (((*str >= 9) && (*str <= 13)) || *str == 32)
		str++;
	if ((*str == '-') || (*str == '+'))
	{	
		if (*str == '-')
			minus = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (minus * number);
}
