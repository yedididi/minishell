/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:43:20 by boran             #+#    #+#             */
/*   Updated: 2023/08/28 15:23:41 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parse.h"

void	ft_addtoken(t_token **head, int type, char *data)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token || !data)
		ft_error(ALLO, NULL);
	new_token->type = type;
	new_token->data = data;
	new_token->next_tkn = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while ((*head)->next_tkn)
			*head = (*head)->next_tkn;
		(*head)->next_tkn = new_token;
		*head = tmp;
	}
}

void	ft_addword(t_wd **head, t_token *token)
{
	t_wd	*new_word;
	t_wd	*tmp;

	new_word = malloc(sizeof(t_wd));
	if (!new_word)
		ft_error(ALLO, NULL);
	new_word->word = token->data;
	new_word->expanded = NULL;
	new_word->next_wd = NULL;
	if (!*head)
		*head = new_word;
	else
	{
		tmp = *head;
		while ((*head)->next_wd)
			*head = (*head)->next_wd;
		(*head)->next_wd = new_word;
		*head = tmp;
	}
}

t_rdr	*ft_newredir(t_token *token_rdr, t_token *token_file)
{
	t_rdr	*new_redir;

	new_redir = malloc(sizeof(t_rdr));
	if (!new_redir)
		ft_error(ALLO, NULL);
	if (ft_strcmp(token_rdr->data, "<"))
		new_redir->type = in_rdr;
	else if (ft_strcmp(token_rdr->data, ">"))
		new_redir->type = out_rdr;
	else if (ft_strcmp(token_rdr->data, "<<"))
		new_redir->type = inin_rdr;
	else
		new_redir->type = outout_rdr;
	new_redir->filename = token_file->data;
	new_redir->expanded = NULL;
	new_redir->prev_rdr = new_redir;
	new_redir->next_rdr = new_redir;
	return (new_redir);
}

void	ft_addredir(t_rdr **head, t_token *token_rdr, t_token *token_file)
{
	t_rdr	*new_redir;
	t_rdr	*tmp;

	new_redir = ft_newredir(token_rdr, token_file);
	if (!*head)
		*head = new_redir;
	else
	{
		tmp = *head;
		while ((*head)->next_rdr != tmp)
			*head = (*head)->next_rdr;
		(*head)->next_rdr = new_redir;
		tmp->prev_rdr = new_redir;
		new_redir->prev_rdr = *head;
		new_redir->next_rdr = tmp;
		*head = tmp;
	}
}

void	ft_addgroup(t_group **head, t_wd *word, t_rdr *redir)
{
	t_group	*new_group;
	t_group	*tmp;

	new_group = malloc(sizeof(t_group));
	if (!new_group)
		ft_error(ALLO, NULL);
	new_group->wd_head = word;
	new_group->rdr_head = redir;
	while (redir && redir->next_rdr != new_group->rdr_head)
		redir = redir->next_rdr;
	new_group->rdr_tail = redir;
	new_group->prev_group = NULL;
	new_group->next_group = NULL;
	if (!*head)
		*head = new_group;
	else
	{
		tmp = *head;
		while ((*head)->next_group)
			*head = (*head)->next_group;
		(*head)->next_group = new_group;
		new_group->prev_group = *head;
		*head = tmp;
	}
}
