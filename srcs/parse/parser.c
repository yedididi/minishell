/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:16:56 by boran             #+#    #+#             */
/*   Updated: 2023/08/17 11:17:33 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	ft_lexer(char *line, int *l)
{
	int	len;
	int	type;

	if (*line == '|')
	{
		len = 1;
		type = pipe_tkn;
	}
	else if (*line == '<' || *line == '>')
	{
		len = 1;
		if (*(line + 1) == *line)
			++len;
		type = redir_tkn;
	}
	else
	{
		len = 0;
		while (line[len] && !ft_isspace(line[len]) && line[len] != '|' \
				&& line[len] != '<' && line[len] != '>')
			++len;
		type = word_tkn;
	}
	*l = len;
	return (type);
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
		else
		{
			ft_addtoken(&tokens, ft_lexer(line, &len), ft_strndup(line, len));
			line += len;
		}
	}
	if (ft_is_invalid(tokens))
		return (NULL);
	return (tokens);
}

void	ft_parser_loop(t_token **tokens, t_wd **word, t_rdr **redir)
{
	while (*tokens && (*tokens)->type != pipe_tkn)
	{
		if ((*tokens)->type == redir_tkn)
		{
			if ((*tokens)->next_tkn->type == word_tkn)
			{
				ft_addredir(redir, (*tokens)->data, (*tokens)->next_tkn->data);
				*tokens = (*tokens)->next_tkn;
			}
			else
				ft_addredir(redir, (*tokens)->data, NULL);
			*tokens = (*tokens)->next_tkn;
		}
		else if ((*tokens)->type == word_tkn)
		{
			ft_addword(word, (*tokens)->data);
			*tokens = (*tokens)->next_tkn;
		}
	}
}

t_group	*ft_parser(t_token *tokens)
{
	t_wd	*word;
	t_rdr	*redir;
	t_group	*groups;

	groups = NULL;
	while (tokens)
	{
		word = NULL;
		redir = NULL;
		while (tokens && tokens->type == word_tkn)
		{
			ft_addword(&word, tokens->data);
			tokens = tokens->next_tkn;
		}
		ft_parser_loop(&tokens, &word, &redir);
		if (word || redir)
			ft_addgroup(&groups, word, redir);
		if (tokens && tokens->type == pipe_tkn)
		{
			tokens = tokens->next_tkn;
			if (tokens && tokens->type == pipe_tkn)
				break ;
		}
	}
	return (groups);
}
