/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:37:32 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/10 13:26:28 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	start_shell(void)
{
	char	*line;

    while (1)
    {
        line = readline("minishell $ ");
        if (!line) //ctrl+d
            break ;
        if (*line != '\0')
            add_history(line);
        if (*line != '\0' && is_whitespace(line) == 0)
        {
            parse();
            execute();
        }
        free(line);
    }
}
