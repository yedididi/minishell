/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:32:38 by boran             #+#    #+#             */
/*   Updated: 2023/08/28 19:44:00 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_fill_expand(char *expand, char *word, char *exit_status, int i)
{
	int		j;
	int		exit_status_len;

	exit_status_len = ft_strlen(exit_status);
	j = 0;
	while (j < i)
	{
		expand[j] = word[j];
		++j;
	}
	while (j < i + exit_status_len)
	{
		expand[j] = exit_status[j - i];
		++j;
	}
	i += 2;
	while (word[i])
	{
		expand[j] = word[i];
		++j;
		++i;
	}
	expand[j] = '\0';
	return (expand);
}

char	*ft_do_expansion(char **expanded, char *word, int start, int ishead)
{
	char	*exit_status;
	int		exit_status_len;
	char	*result;

	exit_status = ft_itoa(ishead * g_exit_status + !ishead * 0);
	if (!exit_status)
		ft_error(ALLO, NULL);
	exit_status_len = ft_strlen(exit_status);
	result = malloc(ft_strlen(word) - 2 + exit_status_len + 1);
	if (!result)
		ft_error(ALLO, NULL);
	result = ft_fill_expand(result, word, exit_status, start);
	*expanded = ft_update_expanded(*expanded, \
	result, start + 1, exit_status_len);
	exit_status = ft_free(exit_status);
	ft_free(word);
	return (result);
}

int	ft_pass_single_quote(char *expanded, char *word, int i)
{
	int	j;

	if (expanded && expanded[i] == '0')
	{
		j = ft_quote_pos(word, i);
		while (j && expanded[j] == '1')
			j = ft_quote_pos(word, j);
		if (j)
			i = j - 1;
	}
	else if (!expanded)
	{
		j = ft_quote_pos(word, i);
		if (j)
			i = j - 1;
	}
	return (i);
}

char	*ft_check_sign(char **expanded, char *word, int ishead, int flag)
{
	int	i;

	i = 0;
	if (!flag)
		return (word);
	while (word[i] && word[i + 1])
	{
		if (word[i] == '\'')
			i = ft_pass_single_quote(*expanded, word, i);
		else if (word[i] == '$' && word[i + 1] == '?')
		{
			if (*expanded && (*expanded)[i] == '0' && (*expanded)[i + 1] == '0')
				word = ft_do_expansion(expanded, word, i, ishead);
			else if (!*expanded)
				word = ft_do_expansion(expanded, word, i, ishead);
		}
		++i;
	}
	return (word);
}

void	ft_expand_exit_status(t_group *groups)
{
	t_wd	*wd;
	t_rdr	*rdr;
	int		ishead;

	ishead = 1;
	while (groups)
	{
		wd = groups->wd_head;
		while (wd)
		{
			wd->word = ft_check_sign(&wd->expanded, wd->word, ishead, 1);
			wd = wd->next_wd;
		}
		rdr = groups->rdr_head;
		while (rdr && rdr->filename)
		{
			rdr->filename = ft_check_sign(&rdr->expanded, \
					rdr->filename, ishead, rdr->type != inin_rdr);
			if (rdr->next_rdr == groups->rdr_head)
				break ;
			rdr = rdr->next_rdr;
		}
		ishead = 0;
		groups = groups->next_group;
	}
}
