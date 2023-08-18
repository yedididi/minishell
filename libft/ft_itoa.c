/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:07:52 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/16 12:58:20 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"

int	get_str_len(int a)
{
	int	len;

	len = 0;
	if (a == 0)
		return (1);
	else if (a < 0)
		len++;
	while (a)
	{
		len++;
		a = a / 10;
	}
	return (len);
}

char	*put_num_str(unsigned int a, char *return_str, int len)
{
	if (a / 10)
		return_str = put_num_str(a / 10, return_str, len - 1);
	return_str[len] = (a % 10) + '0';
	return (return_str);
}

char	*ft_itoa(int a)
{
	int				len;
	unsigned int	num;
	char			*return_str;

	num = 0;
	len = get_str_len(a);
	return_str = (char *)malloc(sizeof(char) * (len + 1));
	if (return_str == 0)
		return (0);
	if (a < 0)
	{
		return_str[0] = '-';
		num = (-1) * a;
	}
	else
		num = a;
	return_str = put_num_str(num, return_str, len - 1);
	return_str[len] = '\0';
	return (return_str);
}
