/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:53:52 by boran             #+#    #+#             */
/*   Updated: 2023/08/18 17:56:54 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_replace(char **str, int start, int end, \
		t_env_node *env, int value_len)
{
	char	*result;
	int		i;

	result = malloc(ft_strlen(*str) - (end - start) + value_len);
	if (!result)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < start)
	{
		result[i] = (*str)[i];
		++i;
	}
	while (i < start + value_len)
	{
		result[i] = env->value[i - start];
		++i;
	}
	while ((*str)[end])
		result[i++] = (*str)[end++];
	result[i] = '\0';
	free(*str);
	return (result);
}

void	ft_replace_env(char **str, int start, t_env_node *env)
{
	int		end;
	char	*key;

	end = start;
	while ((*str)[end] && (*str)[end] != '/')
		++end;
	key = ft_strndup(*str + start, end - start);
	if (!key)
		exit(EXIT_FAILURE);
	while (env)
	{
		if (ft_strcmp(key, env->variable))
		{
			key = ft_free(key);
			break ;
		}
		env = env->next_node;
	}
	if (!env)
		*str = ft_replace(str, start, end, env, 0);
	else
		*str = ft_replace(str, start, end, env, ft_strlen(env->value));
}

void	ft_expansion(t_group *groups)
{
	int		i;
	t_wd	*words;
	t_rdr	*redirs;

	while (groups)
	{
		words = groups->wd_head;
		redirs = groups->rdr_head;
		while (words)
		{
			i = 0;
			while (words->word[i])
			{
				if (words->word[i] == '$')
					ft_replace_env(&words->word, ++i, groups->env_head);
				++i;
			}
			words = words->next_wd;
		}
		while (redirs)
		{
			i = 0;
			while (redirs->filename[i])
			{
				if (redirs->filename[i] == '$')
					ft_replace_env(&redirs->filename, ++i, groups->env_head);
				++i;
			}
		}
		groups = groups->next_group;
	}
}
/*
void	ft_quote(t_group *groups)
{
}
*/
void	ft_print(t_group *group)
{
	t_wd	*words;
	t_rdr	*redirs;

	printf("--------------------------------------------------\n");
	while (group)
	{
		words = group->wd_head;
		printf("<words>\n");
		while (words)
		{
			printf("%s\n", words->word);
			words = words->next_wd;
		}
		printf("=========================================\n");
		printf("<redirs>\n");
		redirs = group->rdr_head;
		if (redirs)
		{
			do {
				printf("%d	%s\n", redirs->type, redirs->filename);
				redirs = redirs->next_rdr;
			}	while (redirs != group->rdr_head);
		}
		group = group->next_group;
	}
	printf("--------------------------------------------------\n");
}

void	ft_parse(t_minishell *minishell, char **envp, char *line)
{
	t_group	*tmp;

	minishell->group_head = ft_parser(ft_tokenizer(line));
	ft_print(minishell->group_head);
	printf("\n\n++++++++++++++++++++++++++++++++\n\n\n");
	tmp = minishell->group_head;
	while (tmp)
	{
		tmp->pipe[0] = -1;
		tmp->pipe[1] = -1;
		tmp->pid = 0;
		tmp->out_len = 0;
		tmp->envp = envp;
		tmp->env_head = minishell->env_head;
		tmp = tmp->next_group;
	}
	minishell->group_head->env_head->variable = ft_strndup("HOME", 4);
	minishell->group_head->env_head->value = ft_strndup("boran", 5);
	minishell->group_head->env_head->next_node = NULL;
	ft_expansion(minishell->group_head);
	ft_print(minishell->group_head);
//	ft_quote(minishell->group_head);
	heredoc(minishell->group_head);
}
