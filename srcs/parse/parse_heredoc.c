/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:19:15 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 16:43:10 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	fill_heredoc(t_rdr *rdr, int random_fd)
{
	int		status;
	pid_t	pid;
	char	*str;

	pid = fork();
	if (pid == 0)
	{
		str = get_next_line(0);
		while (str)
		{
			write(random_fd, str, ft_strlen(str));
			str = get_next_line(0);
		}
		close(random_fd);
		exit(0);
	}
	else if (pid == -1)
		error();
	waitpid(pid, &status, 0);
	EXIT_STATUS = WEXITSTATUS(status);
	close(random_fd);
	rdr->type = out_rdr;
}

int	ch_outout(t_rdr *rdr)
{
	char			random_name[8];
	int				random_fd;
	DIR				*tmp_dir;
	struct dirent	*tmp_info;
	char            *dir_file;
    int             i;

	i = 0;
	random_fd = open("/dev/urandom", O_RDONLY);
	if (read(random_fd, random_name, 8) == -1)
		error();
	close(random_fd);
	while (8 > i)
	{
		if (random_name[i] < 0)
			random_name[i] = random_name[i] * -1;
		random_name[i] = random_name[i] % 26 + 'a';
		i++;
	}
	rdr->filename = ft_strdup(random_name);
	tmp_dir = opendir("/tmp");
	tmp_info = readdir(tmp_dir);
	while (tmp_info)
	{
		if (ft_strncmp(random_name, tmp_info->d_name, 8) == 0)
		{
			closedir(tmp_dir);
			return (0);
		}
		tmp_info = readdir(tmp_dir);
	}
	dir_file = ft_strjoin("/tmp/", random_name);
	random_fd = open(dir_file, O_RDWR | O_CREAT | O_APPEND, 0644); //random file open
	free(dir_file);
	fill_heredoc(rdr, random_fd);
	return (1);
}

void	heredoc(t_group	*group_head)
{
	t_group	*group;
	t_rdr	*rdr;

	group = group_head;
	while (group)
	{
		rdr = group->rdr_head;
		while (rdr)
		{
			if (rdr->type == inin_rdr)
			{
				while (1)
				{
					if (ch_outout(rdr) == 1)
						break ;
				}
			}
			if (rdr == group->rdr_tail)
				break ;
			rdr = rdr->next_rdr;
		}
		group = group->next_group;
	}
}