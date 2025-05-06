/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:09 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/25 14:11:59 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_env_list(t_minishell *minishell)
{
	minishell->env_head = (t_env_node *)malloc(sizeof(t_env_node));
	if (minishell->env_head == 0)
		malloc_fail();
	minishell->env_head->variable = 0;
	minishell->env_head->value = 0;
	minishell->env_head->next_node = 0;
}

t_env_node	*create_new_envnode(char *variable, char *value)
{
	t_env_node	*newnode;

	newnode = (t_env_node *)malloc(sizeof(t_env_node));
	if (newnode == 0)
		malloc_fail();
	newnode->next_node = NULL;
	newnode->variable = variable;
	newnode->value = value;
	return (newnode);
}

void	add_new_envnode(char *variable, char *value, t_env_node *env_head)
{
	t_env_node	*newnode;
	t_env_node	*before_tail_node;

	newnode = create_new_envnode(variable, value);
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

void	free_envnode(t_env_node *node)
{
	if (node == NULL)
		return ;
	free(node->variable);
	node->variable = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

t_env_node	*search_envnode(char *variable, t_env_node *env_head)
{
	t_env_node	*node;

	node = env_head;
	while (node)
	{
		if (ft_strncmp(variable, node->variable, ft_strlen(variable)) == 0)
			return (node);
		node = node->next_node;
	}
	return (NULL);
}
