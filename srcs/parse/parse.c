/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:53:52 by boran             #+#    #+#             */
/*   Updated: 2023/08/29 17:24:54 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_parse_loop(t_minishell *minishell, char **envp)
{
	t_group	*tmp;

	tmp = minishell->group_head;
	while (tmp)
	{
		tmp->pipe[0] = -1;
		tmp->pipe[1] = -1;
		tmp->pid = 0;
		tmp->out_len = 0;
		tmp->in_len = 0;
		tmp->in_err = 0;
		tmp->ctrl = 0;
		tmp->envp = envp;
		tmp->home = ft_strdup(minishell->home);
		tmp->env_head = minishell->env_head->next_node;
		tmp->heredoc_stop = 0;
		tmp = tmp->next_group;
	}
}

void	ft_arrange_group_list(t_group **groups)
{
	t_group	*cur;
	t_group	*tmp;

	cur = *groups;
	while (cur && cur->next_group)
	{
		if (!cur->next_group->wd_head && !cur->next_group->rdr_head)
		{
			tmp = cur->next_group;
			cur->next_group = cur->next_group->next_group;
			tmp->home = ft_free(tmp->home);
			tmp = ft_free(tmp);
		}
		cur = cur->next_group;
	}
	if (*groups && !(*groups)->wd_head && !(*groups)->rdr_head)
	{
		tmp = (*groups)->next_group;
		ft_free((*groups)->home);
		ft_free(*groups);
		*groups = tmp;
	}
}

void	search_for_ctrl(t_group *group)
{
	int		i;
	t_group	*tmp;

	i = -1;
	tmp = group;
	while (tmp)
	{
		if (tmp->wd_head)
		{
			if (ft_strncmp("cat\0", tmp->wd_head->word, 4) == 0)
				tmp->ctrl = i++;
			if (ft_strncmp("grep\0", tmp->wd_head->word, 4) == 0)
				tmp->ctrl = i++;
			if (ft_strncmp("/bin/cat\0", tmp->wd_head->word, 8) == 0)
				tmp->ctrl = i++;
			if (ft_strncmp("/usr/bin/grep\0", tmp->wd_head->word, 13) == 0)
				tmp->ctrl = i++;
		}
		tmp = tmp->next_group;
	}
}

int	ft_check_pipe_space(char *line)
{
	int	i;
	int	pipe_space;

	i = 0;
	pipe_space = 0;
	while (line[i])
	{
		if (line[i] != '|' && !ft_isspace(line[i]))
			pipe_space = 0;
		else if (pipe_space == 0 && line[i] == '|')
			pipe_space = 1;
		else if (pipe_space == 1 && ft_isspace(line[i]))
			pipe_space = 2;
		else if (pipe_space == 2 && line[i] == '|')
		{
			ft_error(PIPE, NULL);
			return (0);
		}
		++i;
	}
	return (1);
}

void	ft_parse(t_minishell *minishell, char **envp, char *line)
{
	t_group	*tmp;

	if (!ft_check_pipe_space(line))
		return ;
	minishell->group_head = ft_parser(ft_tokenizer(line));
	ft_parse_loop(minishell, envp);
	ft_remove_dollar_before_closed_quote(minishell->group_head);
	ft_expansion(minishell->group_head);
	ft_expand_exit_status(minishell->group_head);
	ft_remove_quote(minishell->group_head);
	ft_check_rdr_valid(minishell->group_head);
	ft_arrange_group_list(&minishell->group_head);
	if (!minishell->group_head)
		g_exit_status = 0;
	heredoc(minishell->group_head);
	tmp = minishell->group_head;
	while (tmp)
	{
		tmp->env_head = minishell->env_head;
		tmp = tmp->next_group;
	}
	search_for_ctrl(minishell->group_head);
}
