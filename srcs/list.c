/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:09 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/10 13:26:33 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_list()
{
	// env_info->head = (t_env_node *)malloc(sizeof(t_env_node));
	// env_info->tail = (t_env_node *)malloc(sizeof(t_env_node));
	// if (env_info->head == 0 || env_info->tail == 0)
	// 	error('y');
	// env_info->head->variable = 0;
	// env_info->tail->variable = 0;
	// env_info->head->value = 0;
	// env_info->tail->value = 0;
	// env_info->head->next_node = env_info->tail;
	// env_info->tail->next_node = 0;
	
	env_head = (t_env_node *)malloc(sizeof(t_env_node));
	if (env_head == 0)
		error();
	env_head->variable = 0;
	env_head->value = 0;
	env_head->next_node = 0;
}

t_env_node	*create_newnode(char *variable, char *value)
{
	t_env_node	*newnode;

	newnode = (t_env_node *)malloc(sizeof(t_env_node));
	if (newnode == 0)
		error('y');
	newnode->next_node = 0;
	newnode->variable = variable;
	newnode->value = value;
	return (newnode);
}

void	add_newnode(char *variable, char *value)
{
	// t_env_node	*newnode;
    // t_env_node  *before_tail_node;

	// newnode = create_newnode(value);
	// newnode->next_node = env_info->tail;
    // before_tail_node = env_info->head;
    // while (1)
    // {
    //     if (before_tail_node->next_node == env_info->tail)
    //         break ;
    //     before_tail_node = before_tail_node->next_node;
    // }
	// before_tail_node->next_node = newnode;

	t_env_node	*newnode;
    t_env_node  *before_tail_node;

	newnode = create_newnode(value);
	newnode->next_node = NULL;
    before_tail_node = env_head;
    while (1)
    {
        if (before_tail_node->next_node == 0)
            break ;
        before_tail_node = before_tail_node->next_node;
    }
	before_tail_node->next_node = newnode;
}

char    *get_variable(char *envp)
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

char    *get_value(char *envp)
{
	char	*value
	int		until
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