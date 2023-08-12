/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:12 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 11:23:32 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_list	*ft_tokenize(char *line)
{
	t_list	*token;
	int		len;

	token = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			++line;
		else
		{
			len = 0;
			while (!ft_isspace(line[len]))
				++len;
			ft_lstadd(&token, ft_newnode(ft_strndup(line, len)));
			line += len;
		}
	}
	return (token);
}
