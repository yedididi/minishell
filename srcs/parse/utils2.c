/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:47:17 by boran             #+#    #+#             */
/*   Updated: 2023/08/27 11:07:44 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	ft_is_invalid(t_token *tokens)
{
	if (tokens->type == pipe_tkn)
		return (ft_error(PIPE, NULL));
	while (tokens)
	{
		if (tokens->type == redir_tkn)
		{
			if (!tokens->next_tkn)
				return (ft_error(SNTX, "newline"));
			else if (tokens->next_tkn->type != word_tkn)
				return (ft_error(SNTX, tokens->next_tkn->data));
		}
		if (!tokens->next_tkn && tokens->type == pipe_tkn)
			return (ft_error(PIPE, NULL));
		tokens = tokens->next_tkn;
	}
	return (0);
}

void	ft_check_rdr_valid(t_group *groups)
{
	t_rdr	*rdrs;

	while (groups)
	{
		rdrs = groups->rdr_head;
		while (rdrs)
		{
			if (!rdrs->filename)
				rdrs->filename = ft_strndup("", 0);
			if (rdrs->next_rdr == groups->rdr_head)
				break ;
			rdrs = rdrs->next_rdr;
		}
		groups = groups->next_group;
	}
}

t_token	*ft_next_token(t_token **token, int isword)
{
	t_token	*tmp;

	tmp = (*token)->next_tkn;
	if (!isword)
		(*token)->data = ft_free((*token)->data);
	token = ft_free(*token);
	return (tmp);
}

void	ft_cleartkn(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next_tkn;
		(*tokens)->data = ft_free((*tokens)->data);
		*tokens = ft_free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

int	ft_error(int errno, char *errstr)
{
	if (errno == ALLO)
	{
		printf("minishell: failed to allocation memory with malloc()\n");
		exit(EXIT_FAILURE);
	}
	if (errno == SNTX)
	{
		printf("minishell: syntax error near unexpected token ");
		printf("`%s\'\n", errstr);
	}
	if (errno == PIPE)
		printf("minishell: syntax error near unexpected token `|\'\n");
	return (1);
}
