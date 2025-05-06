/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 15:59:54 by yejlee2          ###   ########.fr       */
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
			g_exit_status = fork_for_pipe(group);
		else
			g_exit_status = execute_group(group);
		group = group->next_group;
	}
	end_input(minishell->group_head);
}

int	fork_for_pipe(t_group *group)
{
	int	exit_num;

	if (group->next_group)
	{
		if (pipe(group->pipe) < 0)
			pipe_fail();
	}
	if (group->prev_group && group->prev_group->prev_group)
	{
		close(group->prev_group->prev_group->pipe[0]);
		close(group->prev_group->prev_group->pipe[1]);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	group->pid = fork();
	if (group->pid < 0)
		fork_fail();
	else if (group->pid == 0)
	{
		exit_num = execute_group_pipe(group);
		exit (exit_num);
	}
	return (0);
}

int	execute_group(t_group *group)
{
	int		status;
	pid_t	pid;

	pid = 0;
	get_rdr_len(group);
	if (group->out_len != 0 || group->in_len != 0)
	{
		pid = fork();
		if (pid < 0)
			fork_fail();
		else if (pid == 0)
			rdr_child(group);
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		return (g_exit_status);
	}
	else
		return (execute_cmd(group));
	return (0);
}

void	rdr_child(t_group *group)
{
	int	*in_fd;
	int	*out_fd;

	out_fd = NULL;
	in_fd = NULL;
	if (group->rdr_head->type == in_rdr)
	{
		in_fd = dup_in_fd(group);
		out_fd = dup_out_fd(group);
	}
	else
	{
		out_fd = dup_out_fd(group);
		in_fd = dup_in_fd(group);
	}
	g_exit_status = execute_cmd(group);
	fd_close(group, out_fd, in_fd);
	exit(g_exit_status);
}

void	fd_close(t_group *group, int *out_fd, int *in_fd)
{
	while (group->out_len)
	{
		close(out_fd[group->out_len]);
		group->out_len--;
	}
	while (group->in_len)
	{
		close(in_fd[group->in_len]);
		group->in_len--;
	}
	free(out_fd);
	free(in_fd);
}
