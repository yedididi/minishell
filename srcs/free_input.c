/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:55:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/26 12:35:18 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_input(t_group *group_head)
{
	t_group	*group;
	t_group	*tmp;

	group = group_head;
	while (group)
	{
		tmp = group->next_group;
		free_wd(group->wd_head);
		free_rdr(group->rdr_head);
		group->home = ft_free(group->home);
		group->wd_head = NULL;
		group->rdr_head = NULL;
		free(group);
		group = tmp;
	}
}

void	free_wd(t_wd *wd_head)
{
	t_wd	*wd;
	t_wd	*tmp;

	wd = wd_head;
	while (wd)
	{
		tmp = wd->next_wd;
		wd->word = ft_free(wd->word);
		wd = ft_free(wd);
		wd = tmp;
	}
}

void	free_rdr(t_rdr *rdr_head)
{
	t_rdr	*rdr;
	t_rdr	*tmp;

	rdr = rdr_head;
	while (rdr)
	{
		tmp = rdr->next_rdr;
		rdr->filename = ft_free(rdr->filename);
		rdr = ft_free(rdr);
		if (tmp == rdr_head)
			break ;
		rdr = tmp;
	}
}
