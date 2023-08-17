/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:53:52 by boran             #+#    #+#             */
/*   Updated: 2023/08/17 16:43:17 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

// void	ft_expansion(t_minishell *minishell)
// {
// }

void	ft_parse(t_minishell *minishell, char **envp, char *line)
{
	t_group	*tmp;

	minishell->group_head = ft_parser(ft_tokenizer(line));
	tmp = minishell->group_head;
	while (tmp)
	{
		tmp->pipe[0] = -1;
		tmp->pipe[1] = -1;
		tmp->pid = 0;
		tmp->out_len = 0;
		tmp->envp = envp;
		tmp->env_head = minishell->env_head;
		tmp = tmp->next_group;
	}
	heredoc(minishell->group_head);
}
