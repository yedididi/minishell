/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:17:28 by boran             #+#    #+#             */
/*   Updated: 2023/08/28 17:19:12 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../libft/libft.h"

int	ft_quote_pos(char *str, int first)
{
	int	second;

	second = first + 1;
	while (str[second])
	{
		if (str[second] == str[first])
			return (second);
		++second;
	}
	return (0);
}

char	*ft_remove(char **str, int first, int second)
{
	char	*result;
	int		i;

	result = malloc(ft_strlen(*str) - 2 + 1);
	if (!result)
		ft_error(ALLO, NULL);
	i = 0;
	while (i < first)
	{
		result[i] = (*str)[i];
		++i;
	}
	while (++first < second)
	{
		result[i] = (*str)[first];
		++i;
	}
	while ((*str)[++second])
	{
		result[i] = (*str)[second];
		++i;
	}
	result[i] = '\0';
	*str = ft_free(*str);
	return (result);
}

char	*ft_remove_loop(char *str, char **exp)
{
	int		i;
	int		j;

	i = 0;
	while (str && str[i])
	{
		if ((*exp && (*exp)[i] == '1') || (str[i] != '\'' && str[i] != '\"'))
			++i;
		else if (str[i] == '\'' || str[i] == '\"')
		{
			j = ft_quote_pos(str, i);
			while (j && *exp && (*exp)[j] == '1')
				j = ft_quote_pos(str, j);
			if (j)
			{
				str = ft_remove(&str, i, j);
				if (*exp)
					*exp = ft_remove(exp, i, j);
				i = j - 1;
			}
			else
				++i;
		}
	}
	return (str);
}

void	ft_remove_quote(t_group *groups)
{
	t_wd	*wds;
	t_rdr	*rdrs;

	while (groups)
	{
		wds = groups->wd_head;
		while (wds)
		{
			wds->word = ft_remove_loop(wds->word, &wds->expanded);
			wds->expanded = ft_free(wds->expanded);
			wds = wds->next_wd;
		}
		rdrs = groups->rdr_head;
		while (rdrs && rdrs->filename)
		{
			rdrs->filename = ft_remove_loop(rdrs->filename, &rdrs->expanded);
			rdrs->expanded = ft_free(rdrs->expanded);
			if (rdrs->next_rdr == groups->rdr_head)
				break ;
			rdrs = rdrs->next_rdr;
		}
		groups = groups->next_group;
	}
}
