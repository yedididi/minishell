/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 17:00:20 by yejlee2          ###   ########.fr       */
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
				execute_group(group);
				exit (0); //해당 자식 프로세스 종료
			}
			//else, 그러니까 부모 프로세스는 파이프를 더 찾는다
		}
		else //뒤에 파이프, 그룹이 더 없는 경우
		{
			execute_group(group);
			return ;
		}
		group = group->next_group;
	}
	end_input(minishell->group_head);
}

void	execute_group(t_group *group)
{
	t_rdr	*rdr;
	t_rdr	*rdr_in;
	t_rdr	*rdr_out;

	rdr = group->rdr_head;
	rdr_in = NULL;
	//원형연결리스트 (t_rdr) 돌면서 입력 리다이렉션 (<) 찾는다. 또 나오면 갱신함.
	while (1)
	{
		if (rdr->type == IN_RDR)
			rdr_in = rdr;
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
	rdr->fd = open(rdr->filename, O_RDONLY);
	if (rdr->fd == -1)
		error_input();
	//마지막까지 확인한 뒤, 최종 입력 리다이렉션을 명령어의 입력으로 넣어준다. (dup 한번)
	dup2(rdr->fd, STDIN);
	//명령어를 실행
	execute_cmd();
	//명령어의 출력값을 출력 리다이렉션 파일들에게 하나씩 전달해준다. (dup 여러번)
	rdr = group->rdr_head;
	while (1)
	{
		//out_rdr이면 파일 다 열고 fd 저장해두기. (int 배열에 저장, 맨 처음 값은 std_out) 
		if (rdr->type == OUT_RDR)
			//파일 읽고 배열에 fd 저장
			dup2(rdr->fd, rdr->prev_rdr->fd);//이건 나중에 한꺼번에
		if (rdr == group->rdr_tail)
			break ;
		rdr = rdr->next_rdr;
	}
}

void	end_input(t_group *group)
{
	while (group->pid)
	{
		waitpid(group->pid, NULL, 0);
		close(group->pipe[0]);
		close(group->pipe[1]);
		group = group->next_group;
	}
}