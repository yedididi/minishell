/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:16:56 by boran             #+#    #+#             */
/*   Updated: 2023/08/26 18:00:34 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

int	ft_isword(char ch)
{
	if (ch == '|' || ch == '<' || ch == '>')
		return (0);
	return (1);
}

int	ft_lexer(char *line, int *l)
{
	int	len;
	int	type;

	len = 0;
	if (*line == '|')
		type = pipe_tkn;
	else if (*line == '<' || *line == '>')
	{
		if (*(line + 1) == *line)
			++len;
		type = redir_tkn;
	}
	else
	{
		while (line[len] && !ft_isspace(line[len]) && ft_isword(line[len]))
		{
			if (line[len] == '\"' || line[len] == '\'')
				if (ft_quote_pos(line, len))
					len = ft_quote_pos(line, len);
			++len;
		}
		type = word_tkn;
	}
	*l = len + (type != word_tkn);
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
	if (tokens && ft_is_invalid(tokens))
	{
		ft_cleartkn(&tokens);
		return (NULL);
	}
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
				ft_addredir(redir, *tokens, (*tokens)->next_tkn);
				*tokens = ft_next_token(tokens, 0);
			}
			else
				ft_addredir(redir, *tokens, NULL);
			*tokens = ft_next_token(tokens, 1);
		}
		else if ((*tokens)->type == word_tkn)
		{
			ft_addword(word, *tokens);
			*tokens = ft_next_token(tokens, 1);
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
			ft_addword(&word, tokens);
			tokens = ft_next_token(&tokens, 1);
		}
		ft_parser_loop(&tokens, &word, &redir);
		if (word || redir)
			ft_addgroup(&groups, word, redir);
		if (tokens && tokens->type == pipe_tkn)
		{
			tokens = ft_next_token(&tokens, 0);
			if (tokens && tokens->type == pipe_tkn)
				ft_cleartkn(&tokens);
		}
	}
	return (groups);
}
