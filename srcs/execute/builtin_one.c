/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/13 16:48:47 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	env(t_group *group)
{
	t_env_node	*node;

	node = group->env_head->next_node;
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

void	export(t_env_node *env_head, char *str)
{
	int i;
	char *variable;
	char *value;
	char **doub;
	
	//variable=value에서 =기준으로 나누어주자.
	// chk_valid();
	i = 0;
	if ((*str <= '0' && *str >= '9') || *str == '=' || is_whitespace(str) == 0 || str_find_chr(str, '=') == 0) //variable이 숫자나 =로 시작하거나 공백이 있으면 오류
		error_input(); //오류문장출력해야댐
	doub = ft_split(str, '=');


	




	while (*str != '=')
	{
		variable[i++] = *str;
		str++;
	}
	variable[i] = '\0';
	str++;
	i = 0;
	while (*str)
	{
		value[i++] = *str;
		str++;
	}
	value[i] = '\0';
	add_new_envnode(variable, value, env_head);
}

void	unset(t_env_node *env_head, char *variable)
{
	t_env_node	*node;
	
	node = env_head;
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
}

void	cd(char *dirname, t_env_node *env_head)
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
		oldpwd = search_envnode("OLDPWD", env_head);
		pwd = search_envnode("PWD", env_head);
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = dirname;
	}
}
