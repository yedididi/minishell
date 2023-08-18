/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:02:38 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/18 11:09:46 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fill_heredoc(t_rdr *rdr, int random_fd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		heredoc_child(rdr, random_fd);
	else if (pid == -1)
		error();
	waitpid(pid, &status, 0);
	EXIT_STATUS = WEXITSTATUS(status);
	close(random_fd);
	rdr->type = in_rdr;
}

void	heredoc_child(t_rdr *rdr, int random_fd)
{
	char	*str;

	write(1, "> ", 2);
	str = get_next_line(0);
	while (str)
	{
		if (ft_strncmp(str, rdr->stop_str, ft_strlen(rdr->stop_str)) == 0)
		{
			free(str);
			break ;
		}
		write(random_fd, str, ft_strlen(str));
		free(str);
		write(1, "> ", 2);
		str = get_next_line(0);
	}
	close(random_fd);
	exit(0);
}
