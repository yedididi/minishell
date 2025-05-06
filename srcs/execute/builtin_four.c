/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:59:07 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 14:24:03 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*cut_variable(char *str)
{
	char	*variable;
	int		i;

	i = 0;
	variable = (char *)malloc(sizeof(char) * (str_find_chr(str, '=') + 1));
	if (variable == 0)
		malloc_fail();
	while (*str != '=')
	{
		if (ft_isalnum(*str) || *str == '_')
			variable[i++] = *str;
		else
		{
			ft_printf_err("minishell: export: `%s':", str);
			ft_printf_err(" not a valid identifier\n");
			free(variable);
			return (NULL);
		}
		str++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*cut_value(char *str)
{
	int		len;
	char	*value;
	int		i;

	i = 0;
	len = ft_strlen(str) - str_find_chr(str, '=');
	value = (char *)malloc(sizeof(char) * len);
	if (value == 0)
		malloc_fail();
	while (*str != '=')
		str++;
	str++;
	while (*str)
	{
		value[i++] = *str;
		str++;
	}
	value[i] = '\0';
	return (value);
}

char	*get_dirname(t_group *group, t_env_node *env_head)
{
	t_env_node	*node;
	char		*dirname;

	dirname = NULL;
	if (group->wd_head->next_wd == NULL
		|| ft_strncmp("~\0", group->wd_head->next_wd->word, 2) == 0)
		dirname = group->home;
	else if (ft_strncmp("-\0", group->wd_head->next_wd->word, 2) == 0)
	{
		node = search_envnode("OLDPWD", env_head);
		if (node != NULL)
		{
			dirname = node->value;
			printf("%s\n", dirname);
		}
	}
	else
		dirname = group->wd_head->next_wd->word;
	return (dirname);
}

void	change_pwd(t_env_node *pwd, t_env_node *oldpwd)
{
	if (pwd != NULL && oldpwd == NULL)
		pwd->value = getcwd(0, sizeof(char) * 1024);
	else if (pwd == NULL && oldpwd != NULL)
	{
		free(oldpwd->value);
		oldpwd->value = NULL;
	}
	else if (pwd != NULL && oldpwd != NULL)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = getcwd(0, sizeof(char) * 1024);
	}
}

int	is_option_n(char *str)
{
	int	i;

	i = 2;
	if (!(str[0] == '-' && str[1] == 'n'))
		return (0);
	while (str[i])
	{
		if (str[i] == 'n' || str[i] == '\0')
			i++;
		else
			return (0);
	}
	return (1);
}
