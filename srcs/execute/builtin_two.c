/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:31:40 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/13 16:36:55 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void    echo(t_group *group)
{
    t_wd    *wd;

    wd = group->wd_head;
    while (wd)
    {
        ft_putstr_fd(wd->word, 1);
        write(1, " ", 1);
        wd = wd->next;
    }
    write(1, "\n", 1);
}

void    exiit(t_group *group)
{

}