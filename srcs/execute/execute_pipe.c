/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:35:00 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 16:01:27 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	execute_group_pipe(t_group *group)
{
	if (group->prev_group)
	{
		close(group->prev_group->pipe[1]);
		dup2(group->prev_group->pipe[0], STDIN);
		close(group->prev_group->pipe[0]);
	}
	if (group->next_group)
	{
		close(group->pipe[0]);
		dup2(group->pipe[1], STDOUT);
		close(group->pipe[1]);
	}
	g_exit_status = execute_group(group);
	return (g_exit_status);
}

void	end_input(t_group *group_head)
{
	int		status;
	t_group	*group;

	group = group_head;
	while (group)
	{
		if (group->pipe[0] != -1)
		{
			close(group->pipe[0]);
			close(group->pipe[1]);
		}
		group = group->next_group;
	}
	group = group_head;
	while (group)
	{
		if (group->pid != 0)
		{
			waitpid(group->pid, &status, 0);
			g_exit_status = WEXITSTATUS(status);
		}
		group = group->next_group;
	}
}
