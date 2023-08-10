/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:37:32 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/10 09:33:50 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	start_shell(void)
{
	char	*line;

	signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell> ");
        if (line)
        {
            parse();
            execute();
            add_history(line);
            free(line);
        	line = NULL;
        }
        else
            printf("ctrl + d\n");
    }
}

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
	exit(0);
}
