/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:10:37 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 17:03:19 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	unset(t_env_node *env_head, t_wd *wd)
{
	char	*variable;

	while (wd)
	{
		variable = wd->word;
		if (!(ft_isalpha(*variable) || *variable == '_'))
		{
			ft_printf_err("unset: `%s': not a valid identifier\n", variable);
			return (1);
		}
		if (ft_isspecial(variable) == 1)
		{
			ft_printf_err("unset: `%s': not a valid identifier\n", variable);
			return (1);
		}
		unset_this(env_head, variable);
		wd = wd->next_wd;
	}
	return (0);
}

void	unset_this(t_env_node *env_head, char *variable)
{
	t_env_node	*node;
	t_env_node	*prev_node;
	t_env_node	*real_head;

	real_head = env_head;
	node = env_head->next_node;
	prev_node = NULL;
	while (node)
	{
		if (ft_strncmp(variable, node->variable,
				ft_strlen(node->variable)) == 0)
		{
			if (prev_node == NULL)
				real_head->next_node = node->next_node;
			else
				prev_node->next_node = node->next_node;
			free_envnode(node);
			return ;
		}
		prev_node = node;
		node = node->next_node;
	}
}

int	get_env_len(t_env_node *env_head)
{
	int			len;
	t_env_node	*node;

	len = 0;
	node = env_head;
	while (node)
	{
		len++;
		node = node->next_node;
	}
	return (len);
}

int	export_error(char *str)
{
	ft_printf_err("minishell: export: '%s': not a valid identifier\n", str);
	return (1);
}

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, sizeof(char) * 1024);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		ft_printf_err("minishell: pwd: ");
		ft_printf_err("error retrieving current directory: getcwd: ");
		ft_printf_err("cannot access parent directories: ");
		ft_printf_err("No such file or directory\n");
		return (1);
	}
	return (0);
}
