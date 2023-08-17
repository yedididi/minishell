/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:09 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 10:43:53 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(int argc, char *argv[], char *envp[], t_minishell *minishell)
{
	struct termios	new_term;

	//각종 초기화를 진행
	//환경변수 전역변수화
	if (argc != 1)
		error();
	tcgetattr(STDIN_FILENO, &new_term); // STDIN으로부터 터미널 속성을 받아온다
	new_term.c_lflag &= ~(ICANON | ECHOCTL);  // ICANON, ECHOCTL 속성을 off
	new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
	new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용

	//시그널 처리(SIGINT, SIGQUIT 무시)
	set_signal();

	//단일연결리스트로 환경변수 저장해두기.
	envp_to_list(envp, minishell);

	(void)envp;
	(void)argc;
	(void)argv;
}

void	set_signal(void)
{
	signal(SIGINT, handler); // CTRL + C > prompt 출력
	// signal(SIGTERM, handler); // CTRL + D > 쉘 종료 >>> 이미 앞에서 처리함
	signal(SIGQUIT, SIG_IGN); // CTRL + / > 아무것도 안함
}

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
