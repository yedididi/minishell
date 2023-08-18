/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:35:00 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/18 14:51:34 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute_group_pipe(t_group *group)
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
	execute_group(group);
}

void	end_input(t_group *group)
{
	int	status;

	while (group)
	{
		if (group->pid != 0)
			waitpid(group->pid, &status, 0);
		EXIT_STATUS = WEXITSTATUS(status);
		close(group->pipe[0]);
		close(group->pipe[1]);
		group = group->next_group;
	}
}
