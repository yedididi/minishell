/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:41:49 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/22 11:58:32 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	after_percent(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (c == 'p')
		return (ft_putaddress(va_arg(ap, unsigned long long)));
	else if (c == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int)));
	else if (c == 'x')
		return (ft_puthex_small(va_arg(ap, unsigned int)));
	else if (c == 'X')
		return (ft_puthex_big(va_arg(ap, unsigned int)));
	else if (c == '%')
		return (write(2, "%", 1));
	else
		return (0);
}

int	ft_printf_err(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
			sum += after_percent(str[++i], ap);
		else
			sum += write(2, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (sum);
}
