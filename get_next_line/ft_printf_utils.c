/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:55:12 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/22 11:58:29 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (i);
}

void	print_big(long long n)
{
	long long	one;

	if (n / 10)
		print_big(n / 10);
	one = (n % 10) + '0';
	write(2, &one, 1);
}

int	ft_putnbr(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		write(2, "-", 1);
		n = n * (-1);
		len++;
	}
	if (n == -2147483648)
	{
		write (2, "2147483648", 10);
		return (11);
	}
	print_big(n);
	return (nbr_len(n, 10) + len);
}

int	nbr_len(unsigned long long num, int base)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		len++;
		num = num / base;
	}
	return (len);
}

int	ft_putaddress(unsigned long long tmp)
{
	char		*hex;

	hex = "0123456789abcdef";
	write(2, "0x", 2);
	if (tmp == 0)
	{
		write(2, "0", 1);
		return (3);
	}
	if (write_hex(tmp, hex) == 0)
		return (0);
	return (nbr_len(tmp, 16) + 2);
}
