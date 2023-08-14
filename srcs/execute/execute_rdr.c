/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_rdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:55:30 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/14 10:54:46 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_rdr	*find_input_rdr(t_group *group)
{
	t_rdr	*rdr;
	t_rdr	*rdr_in;

	rdr = group->rdr_head;
	rdr_in = NULL;
	//원형연결리스트 (t_rdr) 돌면서 입력 리다이렉션 (<) 찾는다. 또 나오면 갱신함.
	while (1)
	{
		if (rdr->type == in_rdr)
			rdr_in = rdr;
		if (rdr->type == inin_rdr) //heredoc
			heredoc(rdr);
		if (rdr->type == out_rdr || rdr->type == outout_rdr)
			group->out_len++;
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
	if (rdr_in)
	{
		rdr_in->fd = open(rdr_in->filename, O_RDONLY);
		if (rdr_in->fd == -1)
			error_input();
	}
	return (rdr_in);
}

void	heredoc(t_rdr *rdr)
{
	char	*end_str;

	end_str = rdr->filename;
	rdr->fd = open(rdr->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (rdr->fd == -1)
		error_input();
}

int	*find_output_rdr(t_group *group)
{
	t_rdr	*rdr;
	int		*out_fd;
	int		i;

	i = 0;
	rdr = group->rdr_head;
	out_fd = (int *)malloc((sizeof(int) * (group->out_len + 2)));
	if (out_fd == 0)
		error_input();
	out_fd[i++] = STDOUT;
	while (1)
	{
		//out_rdr이면 파일 다 열고 fd 저장해두기. (int 배열에 저장, 맨 처음 값은 std_out)
		if (rdr->type == out_rdr || (rdr->type == outout_rdr && i != group->out_len))
		{
			rdr->fd = open(rdr->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (rdr->fd == -1)
				error_input();
			out_fd[i++] = rdr->fd; //파일 읽고 배열에 fd 저장
		}
		else if (rdr->type == outout_rdr && i == group->out_len)
		{
			rdr->fd = open(rdr->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (rdr->fd == -1)
				error_input();
			out_fd[i++] = rdr->fd; //파일 읽고 배열에 fd 저장
		}
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
	out_fd[i] = 0;
	return (out_fd);
}

if (rdr->type == outout_rdr)
{
	
}