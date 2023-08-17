/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:31:40 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 12:45:06 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	echo(t_group *group)
{
	t_wd	*wd;

	wd = group->wd_head->next_wd;
	while (wd)
	{
		ft_putstr_fd(wd->word, 1);
		write(1, " ", 1);
		wd = wd->next_wd;
	}
	write(1, "\n", 1);
}

void	exiit(t_group *group)
{
	(void)group;
}

void	cd(t_group *group, t_env_node *env_head)
{
	int			ch;
	char		*dirname;
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	if (group->wd_head->next_wd == NULL)
		dirname = search_envnode("HOME", env_head)->value;
	else
		dirname = group->wd_head->next_wd->word;
	ch = chdir(dirname);
	if (ch == 0)
	{
		//change OLDPWD, PWD
		oldpwd = search_envnode("OLDPWD", env_head);
		pwd = search_envnode("PWD", env_head);
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = dirname;
	}
	else
	{
		//print error statement
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(dirname, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
}