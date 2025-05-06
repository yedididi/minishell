/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:31:40 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 15:38:10 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	env(t_group *group)
{
	t_env_node	*node;

	node = group->env_head->next_node;
	if (group->wd_head->next_wd)
	{
		ft_printf_err("env: %s: No such file or directory\n",
			group->wd_head->next_wd->word);
		return (1);
	}
	while (node)
	{
		printf("%s=%s\n", node->variable, node->value);
		node = node->next_node;
	}
	return (0);
}

void	echo(t_group *group)
{
	int		n_flag;
	t_wd	*wd;

	n_flag = 0;
	wd = group->wd_head->next_wd;
	while (wd && is_option_n(wd->word))
	{
		n_flag = 1;
		wd = wd->next_wd;
	}
	while (wd)
	{
		printf("%s", wd->word);
		if (wd->next_wd)
			printf(" ");
		wd = wd->next_wd;
	}
	if (n_flag == 0)
		printf("\n");
}

int	exiit(t_group *group)
{
	printf("exit\n");
	if (group->wd_head->next_wd)
	{
		if (isnumber_str(group->wd_head->next_wd->word))
		{
			if (group->wd_head->next_wd->next_wd)
			{
				ft_printf_err("minishell: exit: too many arguments\n");
				return (1);
			}
			else
				exit_branch(group->wd_head->next_wd->word);
		}
		else
		{
			ft_printf_err("minishell: exit: %s: numeric argument required\n",
				group->wd_head->next_wd->word);
			exit (255);
		}
	}
	exit (0);
	return (0);
}

void	exit_branch(char *word)
{
	if (over_longlong(word) == 1)
	{
		ft_printf_err("minishell: exit: %s: numeric argument required\n", word);
		exit (255);
	}
	else
	{
		if (ft_atol(word) > 0)
			exit(ft_atol(word) % 256);
		else
			exit(ft_atol(word) % 256 + 256);
	}
}

int	cd(t_group *group, t_env_node *env_head)
{
	int			ch;
	char		*dirname;
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	dirname = get_dirname(group, env_head);
	ch = chdir(dirname);
	if (ch == 0)
	{
		pwd = search_envnode("PWD", env_head);
		oldpwd = search_envnode("OLDPWD", env_head);
		change_pwd(pwd, oldpwd);
	}
	else
	{
		ft_printf_err("minishell: cd: %s: No such file or directory\n", dirname);
		return (1);
	}
	return (0);
}
