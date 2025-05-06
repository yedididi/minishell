/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:37:32 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/26 20:57:20 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	start_shell(t_minishell *minishell, char *envp[])
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		line = readline("minishell $ ");
		if (!line)
		{
			print_exit();
			break ;
		}
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && is_whitespace(line) == 0)
		{
			ft_parse(minishell, envp, line);
			if (minishell->group_head
				&& minishell->group_head->heredoc_stop == 0)
				execute(minishell);
			free_input(minishell->group_head);
			minishell->group_head = NULL;
		}
		free(line);
	}
}

void	print_exit(void)
{
	printf("\033[1A");
	printf("\033[10C");
	printf("$ exit\n");
}
