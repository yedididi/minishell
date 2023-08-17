/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 10:41:19 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute(t_minishell *minishell)
{
	t_group	*group;

	group = minishell->group_head;
	while (group)
	{
		if (group->next_group) //뒤에 파이프가 있는 경우
		{
			pipe(group->pipe);
			group->pid = fork();
			if (group->pid < 0) //포크 에러
				error_input(); //그룹이 아닌, 한줄 전체의 입력에 대해서 프로세스를 종료하고, (그러니까 자식 프로세스들만), 부모만 살려 다음 프롬프트 출력 
			else if (group->pid == 0) //자식 프로세스
			{
				execute_group_pipe(group);
				exit (0); //해당 자식 프로세스 종료
			}
			//else, 그러니까 부모 프로세스는 파이프를 더 찾는다
		}
		else //뒤에 파이프, 그룹이 더 없는 경우
		{
			group->pid = fork();
			if (group->pid < 0) //포크 에러
				error_input(); //그룹이 아닌, 한줄 전체의 입력에 대해서 프로세스를 종료하고, (그러니까 자식 프로세스들만), 부모만 살려 다음 프롬프트 출력 
			else if (group->pid == 0) //자식 프로세스
			{
				execute_group(group);
				exit (0); //해당 자식 프로세스 종료
			}
		}
		group = group->next_group;
	}
	end_input(minishell->group_head);
}

void	execute_group(t_group *group)
{
	t_rdr	*rdr_in;
	int		*out_fd;
	int		i;

	i = 0;
	//마지막까지 확인한 뒤, 최종 입력 리다이렉션을 명령어의 입력으로 넣어준다. (dup 한번)
	rdr_in = find_input_rdr(group);
	if (rdr_in)
	{
		dup2(rdr_in->fd, STDIN);
		close(rdr_in->fd); //여기서 닫아도 될가......
	}
	//명령어의 출력값을 출력 리다이렉션 파일들에게 하나씩 전달해준다. (dup 여러번)
	if (group->out_len != 0)
	{
		out_fd = find_output_rdr(group);
		while (out_fd[i + 1] != 0)
		{
			dup2(out_fd[i], out_fd[i + 1]);
			close(out_fd[i]); //여기서 닫아도 될가......
			i++;
		}
	}
	//명령어를 실행
	execute_cmd(group);
}

void	execute_group_pipe(t_group *group)
{
	if (group->prev_group) //전 파이프와 연결
	{
		close(group->prev_group->pipe[1]);
		dup2(group->prev_group->pipe[0], STDIN);
		close(group->prev_group->pipe[0]); //여기서 닫아도 될가..........
	}
	if (group->next_group) //뒤 파이프와 연결
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

	while (group->pid)
	{
		waitpid(group->pid, &status, 0);
		EXIT_STATUS = WEXITSTATUS(status);
		if (group->next_group)
		{
			close(group->pipe[0]);
			close(group->pipe[1]);
		}
		group = group->next_group;
	}
}