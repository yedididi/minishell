/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:15:18 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 17:39:09 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	envp_to_list(char **envp, t_minishell *minishell)
{
	char	*variable;
	char	*value;
	int		i;

	i = 0;
	init_env_list(minishell);
	while (envp[i])
	{
		variable = get_variable(envp[i]);
		value = get_value(envp[i]);
		add_new_envnode(variable, value, minishell->env_head);
		i++;
	}
}

char	*get_variable(char *envp)
{
	char	*variable;
	int		until;
	int		i;

	i = 0;
	until = 0;
	while (envp[until])
	{
		if (envp[until] == '=')
			break ;
		until++;
	}
	variable = (char *)malloc(sizeof(char) * (until + 1));
	if (variable == 0)
		malloc_fail();
	while (until > i)
	{
		variable[i] = envp[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*get_value(char *envp)
{
	char	*value;
	int		until;
	int		i;

	i = 0;
	until = 0;
	while (envp[until])
	{
		if (envp[until] == '=')
			break ;
		until++;
	}
	value = (char *)malloc(sizeof(char) * (ft_strlen(envp) - until));
	if (value == 0)
		malloc_fail();
	while (envp[++until])
	{
		value[i] = envp[until];
		i++;
	}
	value[i] = '\0';
	return (value);
}

void	change_envnode(char *variable, char *value, t_env_node *env_head)
{
	t_env_node	*node;

	node = env_head;
	while (node)
	{
		if (ft_strncmp(variable, node->variable, ft_strlen(variable)) == 0)
		{
			free(variable);
			free(node->value);
			node->value = value;
			return ;
		}
		node = node->next_node;
	}
}
