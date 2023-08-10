/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:00:00 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/22 15:15:43 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if ((*lst == 0) && new)
	{
		*lst = new;
		return ;
	}
	else if (*lst && new)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
	}
	*lst = tmp;
}
