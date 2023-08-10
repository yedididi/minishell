/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:09 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/10 13:05:32 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    init(int argc, char *argv[], char *envp[])
{
	struct termios  new_term;
    
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
	// set_signal();
	(void)envp;
	(void)argc;
	(void)argv;
}