/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/18 14:50:24 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_minishell *minishell)
{
	t_group	*group;

	group = minishell->group_head;
	while (group)
	{
		if (group->next_group || group->prev_group)
		{
			fork_for_pipe(group);
		}
		else
			execute_group(group);
		group = group->next_group;
	}
	end_input(minishell->group_head);
}

void	fork_for_pipe(t_group *group)
{
	if (group->next_group)
		pipe(group->pipe);
	if (group->prev_group && group->prev_group->prev_group)
	{
		close(group->prev_group->prev_group->pipe[0]);
		close(group->prev_group->prev_group->pipe[1]);
	}
	group->pid = fork();
	if (group->pid < 0)
		error_input();
	else if (group->pid == 0)
	{
		execute_group_pipe(group);
		exit (0);
	}
}

void	execute_group(t_group *group)
{
	pid_t	pid;
	t_rdr	*rdr_in;

	pid = 0;
	rdr_in = find_input_rdr(group);
	if (group->out_len != 0 || rdr_in)
	{
		pid = fork();
		if (pid < 0)
			error_input();
		else if (pid == 0)
			rdr_child(rdr_in, group);
		waitpid(pid, NULL, 0);
	}
	else
		execute_cmd(group);
}

void	rdr_child(t_rdr *rdr_in, t_group *group)
{
	int	*out_fd;

	out_fd = NULL;
	if (rdr_in)
		dup2(rdr_in->fd, STDIN);
	if (group->out_len != 0)
	{
		out_fd = find_output_rdr(group);
		dup2(out_fd[group->out_len], STDOUT);
	}
	execute_cmd(group);
	while (group->out_len)
	{
		close(out_fd[group->out_len]);
		group->out_len--;
	}
	close(rdr_in->fd);
	exit(0);
}
