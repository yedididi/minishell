/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_before_closed_quote.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:24:20 by boran             #+#    #+#             */
/*   Updated: 2023/08/29 14:06:19 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"
#include "../libft/libft.h"

char	*ft_fill_str(char **str, int dollar_idx)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen(*str));
	while (i < dollar_idx)
	{
		result[i] = (*str)[i];
		++i;
	}
	while ((*str)[i + 1])
	{
		result[i] = (*str)[i + 1];
		++i;
	}
	result[i] = '\0';
	*str = ft_free(*str);
	return (result);
}

char	*ft_remove_dollar(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && ((*str)[i + 1] == '\'' || \
					(*str)[i + 1] == '\"') && ft_quote_pos(*str, i + 1))
			*str = ft_fill_str(str, i);
		++i;
	}
	return (*str);
}

void	ft_remove_dollar_before_closed_quote(t_group *groups)
{
	t_wd	*wds;
	t_rdr	*rdrs;

	while (groups)
	{
		wds = groups->wd_head;
		while (wds)
		{
			wds->word = ft_remove_dollar(&wds->word);
			wds = wds->next_wd;
		}
		rdrs = groups->rdr_head;
		while (rdrs)
		{
			rdrs->filename = ft_remove_dollar(&rdrs->filename);
			if (rdrs->next_rdr == groups->rdr_head)
				break ;
			rdrs = rdrs->next_rdr;
		}
		groups = groups->next_group;
	}
}
