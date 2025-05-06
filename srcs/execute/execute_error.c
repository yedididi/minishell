/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:03:38 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 17:41:25 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fork_fail(void)
{
	ft_printf_err("fork has failed\n");
	exit(1);
}

void	malloc_fail(void)
{
	ft_printf_err("malloc has failed\n");
	exit(1);
}

void	pipe_fail(void)
{
	ft_printf_err("pipe has failed\n");
	exit(1);
}

void	read_fail(void)
{
	ft_printf_err("read failed\n");
	exit(1);
}
