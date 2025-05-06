/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 17:03:21 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	exportt(t_env_node *env_head, t_wd *wd)
{
	if (wd == NULL)
		print_export(env_head);
	while (wd)
	{
		if (!chk_equal_sign(wd->word) && !is_alpha_and_(wd->word))
			return (export_error(wd->word));
		if (*(wd->word) != '_' && !ft_isalpha(*(wd->word)))
			return (export_error(wd->word));
		else if (chk_equal_sign(wd->word))
		{
			if (export_equal(env_head, wd->word) == 1)
				return (1);
		}
		wd = wd->next_wd;
	}
	return (0);
}

int	export_equal(t_env_node *env_head, char *str)
{
	char	*value;
	char	*variable;

	variable = cut_variable(str);
	value = cut_value(str);
	if (variable == NULL || value == NULL)
	{
		if (variable)
			free(variable);
		if (value)
			free(value);
		return (1);
	}
	if (search_envnode(variable, env_head))
		change_envnode(variable, value, env_head);
	else
		add_new_envnode(variable, value, env_head);
	return (0);
}

void	print_export(t_env_node *env_head)
{
	t_env_node	*node;
	char		**arr;
	int			i;

	i = 0;
	arr = sort_export(env_head);
	while (arr[i])
	{
		node = search_envnode(arr[i], env_head);
		if (node->value != NULL)
			printf("declare -x %s=\"%s\"\n", node->variable, node->value);
		i++;
	}
	free(arr);
}

char	**sort_export(t_env_node *env_head)
{
	t_env_node	*node;
	char		**arr;
	int			i;

	i = 0;
	node = env_head;
	arr = (char **)malloc(sizeof(char *) * (get_env_len(env_head) + 1));
	if (arr == 0)
		exit(1);
	while (node)
	{
		arr[i] = node->variable;
		node = node->next_node;
		i++;
	}
	arr[i] = NULL;
	return (ascii_sort(env_head, arr));
}

char	**ascii_sort(t_env_node *env_head, char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (get_env_len(env_head) - 1 > i)
	{
		j = 0;
		while (get_env_len(env_head) - 1 > j)
		{
			if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j])) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
