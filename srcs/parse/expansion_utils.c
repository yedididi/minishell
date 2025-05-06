/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:55:37 by boran             #+#    #+#             */
/*   Updated: 2023/08/28 20:08:08 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_update_expanded(char *expanded, char *str, int start, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) + 1);
	if (!new)
		ft_error(ALLO, NULL);
	if (!expanded)
		while (i + 1 < start)
			new[i++] = '0';
	else
	{
		while (i + 1 < start)
		{
			new[i] = expanded[i];
			++i;
		}
	}
	while (i + 1 < start + len)
		new[i++] = '1';
	while (str[i])
		new[i++] = '0';
	new[i] = '\0';
	ft_free(expanded);
	return (new);
}

char	*ft_replace(char **str, int key_range[2], \
		t_env_node *env, int value_len)
{
	char	*result;
	int		i;

	if (ft_strlen(*str) - (key_range[1] - key_range[0]) + value_len == 1)
		return (ft_free(*str));
	result = malloc(ft_strlen(*str) - \
			(key_range[1] - key_range[0]) + value_len);
	if (!result)
		ft_error(ALLO, NULL);
	i = 0;
	while (i + 1 < key_range[0])
	{
		result[i] = (*str)[i];
		++i;
	}
	while (i + 1 < key_range[0] + value_len)
	{
		result[i] = env->value[i + 1 - key_range[0]];
		++i;
	}
	while ((*str)[key_range[1]])
		result[i++] = (*str)[key_range[1]++];
	result[i] = '\0';
	*str = ft_free(*str);
	return (result);
}

char	*ft_replace_not_exist(char **str, int key_range[2], char *expanded)
{
	*str = ft_replace(str, key_range, NULL, 0);
	if (!*str)
		return (ft_free(expanded));
	return (ft_update_expanded(expanded, *str, key_range[0], 0));
}

char	*ft_replace_env(char *expanded, char **str, int start, t_env_node *env)
{
	int		key_range[2];
	char	*key;

	key_range[0] = start;
	key_range[1] = start;
	while ((*str)[key_range[1]] && !ft_issymbol((*str)[key_range[1]]))
		++key_range[1];
	key = ft_strndup(*str + key_range[0], key_range[1] - start);
	if (!key)
		ft_error(ALLO, NULL);
	while (env)
	{
		if (ft_strcmp(key, env->variable))
			break ;
		env = env->next_node;
	}
	key = ft_free(key);
	if (!env)
		return (ft_replace_not_exist(str, key_range, expanded));
	*str = ft_replace(str, key_range, env, ft_strlen(env->value));
	if (!*str)
		return (ft_free(expanded));
	return (ft_update_expanded(expanded, *str, start, ft_strlen(env->value)));
}
