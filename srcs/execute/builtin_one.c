/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 11:23:36 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	env(t_minishell *minishell)
{
	t_env_node	*node;

	node = minishell->env_head->next_node;
	while (1)
	{
		ft_putstr_fd(node->variable, 1);
		write(1, "=", 1);
		ft_putstr_fd(node->value, 1);
		write(1, "\n", 1);
		if (node->next_node == 0)
			break ;
		node = node->next_node;
	}
}

void	export(t_minishell *minishell, char *variable, char *value)
{
	// chk_valid();
	add_new_envnode(variable, value, minishell);
}

void	unset(t_minishell *minishell, char *variable)
{
	t_env_node	*node;
	
	node = minishell->env_head;
	while (node)
	{
		if (ft_strncmp(variable, node->next_node->variable, ft_strlen(variable)) == 0)
		{
			node->next_node = node->next_node->next_node;
			free_envnode(node->next_node);
			return ;
		}
		node = node->next_node;
	}
	//no error statement when there is no variable
}

void	pwd(void)
{
	char cwd[256];

   	if (getcwd(cwd, sizeof(cwd)))
    	ft_putstr_fd(cwd, 1);
	else
       	error();
   	return 0;
}

void	cd(char *dirname, t_minishell *minishell)
{
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	if (chdir(dirname) == 1)
	{
		//print error statement
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(dirname, 1);
		ft_putstr_fd(": No such file or directory", 1);
	}
	else
	{
		//change OLDPWD, PWD
		oldpwd = search_envnode("OLDPWD", minishell);
		pwd = search_envnode("PWD", minishell);
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = dirname;
	}
}
