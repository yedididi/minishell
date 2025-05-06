/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:55:30 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 11:58:10 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	*get_int_malloc(int size)
{
	int	*arr;

	arr = (int *)malloc(sizeof(int) * (size));
	if (arr == 0)
		malloc_fail();
	return (arr);
}

int	*find_output_rdr(t_group *group)
{
	t_rdr	*rdr;
	int		*out_fd;
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	rdr = group->rdr_head;
	out_fd = get_int_malloc(group->out_len + 2);
	out_fd[i++] = STDOUT;
	while (1)
	{
		if (rdr->type == out_rdr || rdr->type == outout_rdr)
			tmp = open_out(rdr, rdr->type);
		if (tmp == -1)
			return (NULL);
		if (rdr->type == out_rdr || rdr->type == outout_rdr)
			out_fd[i++] = tmp;
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
	out_fd[i] = 0;
	return (out_fd);
}

int	open_out(t_rdr *rdr, int type)
{
	if (type == out_rdr)
		rdr->fd = open(rdr->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == outout_rdr)
		rdr->fd = open(rdr->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (rdr->fd == -1 && ft_strncmp(rdr->filename, "./", 2) == 0)
	{
		ft_printf_err("minishell: %s: Permission denied\n", rdr->filename);
		close(rdr->fd);
		return (-1);
	}
	else if (rdr->fd == -1)
	{
		ft_printf_err("minishell: %s", rdr->filename);
		ft_printf_err(": No such file or directory\n");
		return (-1);
	}
	return (rdr->fd);
}
