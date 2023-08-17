/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:37:32 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 16:44:14 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	start_shell(t_minishell *minishell, char *envp[])
{
	char	*line;

	(void)envp;
	(void)minishell;
	while (1)
	{
		line = readline("minishell $ ");
		if (!line) //ctrl+d
			break ;
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && is_whitespace(line) == 0)
		{
			ft_parse(minishell, envp, line);
			if (minishell->group_head)
				execute(minishell);
			// free_input(); //file close, free
		}
		free(line);
	}
}
