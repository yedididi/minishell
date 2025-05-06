/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:43:36 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/22 11:59:19 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf_err(const char *str, ...);
int	ft_putstr(char *str);
int	ft_putaddress(unsigned long long tmp);
int	ft_putnbr(long long n);
int	ft_puthex_small(unsigned int nbr);
int	ft_puthex_big(unsigned int nbr);
int	ft_putchar(char c);
int	nbr_len(unsigned long long num, int base);
int	write_hex(unsigned long long nbr, char *hex);

#endif
