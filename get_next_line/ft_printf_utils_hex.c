/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:19:00 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/22 11:58:58 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_hex(unsigned long long nbr, char *hex)
{
	char	*print_str;
	int		len;

	len = nbr_len(nbr, 16);
	print_str = (char *)malloc(sizeof(char) * (len + 1));
	if (print_str == 0)
		return (0);
	print_str[len--] = '\0';
	print_str[len] = '0';
	while (nbr)
	{
		print_str[len--] = hex[nbr % 16];
		nbr = nbr / 16;
	}
	ft_putstr(print_str);
	free(print_str);
	return (1);
}

int	ft_puthex_small(unsigned int nbr)
{
	char			*hex;

	hex = "0123456789abcdef";
	if (write_hex(nbr, hex) == 0)
		return (0);
	return (nbr_len(nbr, 16));
}

int	ft_puthex_big(unsigned int nbr)
{
	char			*hex;

	hex = "0123456789ABCDEF";
	if (write_hex(nbr, hex) == 0)
		return (0);
	return (nbr_len(nbr, 16));
}

int	ft_putchar(char c)
{
	write(2, &c, 1);
	return (1);
}
