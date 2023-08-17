/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:44 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 10:44:21 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell		minishell;	
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	init(argc, argv, envp, &minishell); //변수 및 환경변수 초기화
	start_shell(&minishell, envp); 	//명령 프롬프트 실행,
					//while 문 안에서 입력 받은 후 (파싱 및 유효성검사>실행) 계속 반복
	tcgetattr(STDIN_FILENO, &term);
	return (0);
}

void	error(void)
{
	exit(1);
}
