/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:16:56 by boran             #+#    #+#             */
/*   Updated: 2023/08/14 11:22:40 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
int	ft_quotelen(char *line, char quote)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != quote)
	{
//		if (ft_isspace(line[len]))
//			ft_error(command not found)
		++len;
	}
	if (!line[len])
		return (-1);
	return (len);
}
*/

void	ft_lexer(t_token **token, char *line)
{
}

t_token	*ft_tokenizer(char *line)
{
	t_token	*tokens;
	int		len;

	tokens = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			++line;
		else if (*line == '|')
		{
			ft_addtoken(&tokens, pipe_tkn, ft_strndup(line, 1));
			++line;
			if (*line == '|')
				return (tokens);
		}
		else if (*line == '<' || *line == '>')
		{
			len = 1;
			if (*(line + 1) == *line)
				++len;
			ft_addtoken(&tokens, redir_tkn, ft_strndup(line, len));
			line += len;
		}
		else
		{
			len = 0;
			while (line[len] && !ft_isspace(line[len]) && line[len] != '|' \
					&& line[len] != '<' && line[len] != '>')
				++len;
			ft_addtoken(&tokens, word_tkn, ft_strndup(line, len));
			line += len;
		}
	}
	return (tokens);
}

t_group	*ft_parser(t_token *tokens)
{
	t_token	*tmp;
	t_wd	*word;
	t_rdr	*redir;
	t_group	*groups;

	groups = NULL;
	while(tokens)
	{
		word = NULL;
		redir = NULL;
		while (tokens && tokens->type == word_tkn)
		{
			ft_addword(&word, tokens->data);
			tokens = tokens->next_tkn;
		}
		while (tokens && tokens->type != pipe_tkn)
		{
			if (tokens->type == redir_tkn)
			{
				if (tokens->next_tkn->type == word_tkn)
				{
					ft_addredir(&redir, tokens->data, tokens->next_tkn->data);
					tokens = tokens->next_tkn;
				}
				else
					ft_addredir(&redir, tokens->data, NULL);
				tokens = tokens->next_tkn;
			}
			else if (tokens->type == word_tkn)
			{
				ft_addword(&word, tokens->data);
				tokens = tokens->next_tkn;
			}
		}
		ft_addgroup(&groups, word, redir);
		if (tokens && tokens->type == pipe_tkn)
			tokens = tokens->next_tkn;
	}
	return (groups);
}

t_group  *parse(char *line, t_minishell *minishell)
{
	ft_parser(ft_tokenizer(line));
}