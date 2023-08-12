/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:37:32 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 17:00:16 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	start_shell(void)
{
	char	*line;

    while (1)
    {
        line = readline("minishell $ ");
        if (!line) //ctrl+d
            break ;
        if (*line != '\0')
            add_history(line);
        if (*line != '\0' && is_whitespace(line) == 0)
        {
            // parse(); //자료구조(트리, 연결리스트...)에 명령어들을 토큰 단위로 분리하고 유효성 검사 완료
            execute(); //파이프 기준으로 먼저 나누어 fork, 후에 실행
            free_input();
        }
        free(line);
    }
}
