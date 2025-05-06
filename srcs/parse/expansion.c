/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:42:55 by boran             #+#    #+#             */
/*   Updated: 2023/08/28 20:08:14 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_expand_loop(char **str, t_env_node *env_head)
{
	int		i;
	int		double_quote;
	char	*expanded;

	i = 0;
	double_quote = 0;
	expanded = NULL;
	while (*str && (*str)[i])
	{
		if (!double_quote && (*str)[i] == '\"' && ft_quote_pos(*str, i))
			double_quote = 1;
		else if (double_quote && (*str)[i] == '\"')
			double_quote = 0;
		else if (!double_quote && (*str)[i] == '\'' && ft_quote_pos(*str, i))
			i = ft_quote_pos(*str, i);
		if ((*str)[i] == '$' && !ft_issymbol((*str)[i + 1]) && \
				!ft_isdigit((*str)[i + 1]))
		{
			expanded = ft_replace_env(expanded, str, i + 1, env_head);
			--i;
		}
		++i;
	}
	return (expanded);
}

void	ft_arrange_words_lst(t_wd **words)
{
	t_wd	*cur;
	t_wd	*tmp;

	cur = *words;
	while (cur && cur->next_wd)
	{
		if (!(cur->next_wd->word))
		{
			tmp = cur->next_wd;
			cur->next_wd = cur->next_wd->next_wd;
			tmp = ft_free(tmp);
		}
		cur = cur->next_wd;
	}
	if (*words && !(*words)->word)
	{
		tmp = (*words)->next_wd;
		ft_free(*words);
		*words = tmp;
	}
}

void	ft_expansion(t_group *groups)
{
	t_wd	*wds;
	t_rdr	*rdrs;

	while (groups)
	{
		wds = groups->wd_head;
		while (wds)
		{
			wds->expanded = ft_expand_loop(&wds->word, groups->env_head);
			wds = wds->next_wd;
		}
		rdrs = groups->rdr_head;
		while (rdrs)
		{
			if (rdrs->type != inin_rdr)
				rdrs->expanded \
					= ft_expand_loop(&rdrs->filename, groups->env_head);
			if (rdrs->next_rdr == groups->rdr_head)
				break ;
			rdrs = rdrs->next_rdr;
		}
		ft_arrange_words_lst(&groups->wd_head);
		groups = groups->next_group;
	}
}
