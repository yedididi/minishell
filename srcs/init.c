/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:09 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 17:39:39 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(int argc, char *envp[], t_minishell *minishell)
{
	struct termios	new_term;
	t_env_node		*node;

	if (argc != 1)
	{
		write(2, "Error: ./minishell\n", 19);
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	set_signal();
	envp_to_list(envp, minishell);
	node = search_envnode("HOME", minishell->env_head->next_node);
	minishell->home = ft_strdup(node->value);
}

void	set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
