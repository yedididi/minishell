/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:58:34 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/21 12:54:11 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*re_list;

	re_list = (t_list *)malloc(sizeof(t_list));
	if (re_list == 0)
		return (0);
	re_list->content = content;
	re_list->next = 0;
	return (re_list);
}
