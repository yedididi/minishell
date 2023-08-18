/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:15:18 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 10:42:36 by yejlee2          ###   ########.fr       */
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
	//한 줄 안에서 =를 기준으로 variable과 value를 나누어 노드 생성. 
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
		error();
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
		error();
	while (envp[++until])
	{
		value[i] = envp[until];
		i++;
	}
	value[i] = '\0';
	return (value);
}
