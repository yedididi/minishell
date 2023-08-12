/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:21:12 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 11:21:31 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_list	*ft_newnode(char *data)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd(t_list **head, t_list *node)
{
	t_list	*tmp;

	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}