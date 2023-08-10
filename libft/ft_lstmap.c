/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:04:55 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/22 14:32:22 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	head = 0;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
	}
	tmp = 0;
	return (head);
}
