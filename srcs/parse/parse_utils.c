/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:42:49 by boran             #+#    #+#             */
/*   Updated: 2023/08/18 14:38:52 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	ft_isspace(char ch)
{
	int	i;

	i = 0;
	if (ch == 0)
		return (1);
	while (ch != WHITESPACE[i] && WHITESPACE[i])
		++i;
	if (i < 6)
		return (1);
	return (0);
}

char	*ft_strndup(char *src, int len)
{
	char	*result;
	int		i;

	result = malloc(len);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = src[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	if (!*str1 && !*str2)
		return (1);
	return (0);
}

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int	ft_is_invalid(t_token *tokens)
{
	t_token	*pre;
	t_token	*next;

	pre = tokens;
	if (!pre || !pre->next_tkn)
		return (0);
	while (pre->next_tkn)
	{
		next = pre->next_tkn;
		if (pre->type == redir_tkn && next->type != word_tkn)
		{
			printf("syntax error near unexpected token `%s\'\n", next->data);
			return (1);
		}
		pre = next;
	}
	if (pre->type == pipe_tkn)
	{
		printf("syntax error pipe can't be last token\n");
		return (1);
	}
	return (0);
}
