/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:09:25 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/16 13:02:01 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_big(int n, int fd)
{
	int	one;

	if (n / 10)
		print_big(n / 10, fd);
	one = (n % 10) + '0';
	write(fd, &one, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * (-1);
	}
	if (n == -2147483648)
	{
		write (fd, "2147483648", 10);
		return ;
	}
	print_big(n, fd);
}
