/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:06:29 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 11:51:27 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	get_rdr_len(t_group *group)
{
	t_rdr	*rdr;

	rdr = group->rdr_head;
	while (1)
	{
		if (rdr == NULL)
			return ;
		if (rdr->type == in_rdr)
			group->in_len++;
		if (rdr->type == out_rdr || rdr->type == outout_rdr)
			group->out_len++;
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
}

int	open_in(t_rdr *rdr)
{
	rdr->fd = open(rdr->filename, O_RDONLY);
	if (rdr->fd == -1)
	{
		ft_printf_err("minishell: %s", rdr->filename);
		ft_printf_err(": No such file or directory\n");
		return (-1);
	}
	return (rdr->fd);
}

int	*find_input_rdr(t_group *group)
{
	t_rdr	*rdr;
	int		*in_fd;
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	rdr = group->rdr_head;
	in_fd = get_int_malloc(group->in_len + 1);
	in_fd[i++] = STDIN;
	while (1)
	{
		if (rdr->type == in_rdr)
			tmp = open_in(rdr);
		if (tmp == -1)
			return (NULL);
		if (rdr->type == in_rdr)
			in_fd[i++] = tmp;
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
	in_fd[i] = 0;
	return (in_fd);
}
