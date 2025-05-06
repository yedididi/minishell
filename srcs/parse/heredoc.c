/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:19:15 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/27 17:41:36 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ch_inin(t_rdr *rdr, t_group *group_head)
{
	char	*random_name;
	int		random_fd;
	char	*dir_file;

	random_name = make_random_file();
	rdr->stop_str = ft_strjoin(rdr->filename, "\n");
	free(rdr->filename);
	dir_file = ft_strndup(random_name, 8);
	if (chk_for_dup_file(random_name) == 0)
		return (0);
	free(random_name);
	rdr->filename = ft_strjoin("/tmp/", dir_file);
	random_fd = open(rdr->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(dir_file);
	if (fill_heredoc(rdr, random_fd) == 1)
		group_head->heredoc_stop = 1;
	free(rdr->stop_str);
	return (1);
}

char	*make_random_file(void)
{
	char	random_name[8];
	int		random_fd;
	int		i;

	i = 0;
	random_fd = open("/dev/urandom", O_RDONLY);
	if (read(random_fd, random_name, 8) == -1)
		read_fail();
	close(random_fd);
	while (8 > i)
	{
		if (random_name[i] < 0)
			random_name[i] = random_name[i] * -1;
		random_name[i] = random_name[i] % 26 + 'a';
		i++;
	}
	return (ft_strndup(random_name, 8));
}

int	chk_for_dup_file(char *random_name)
{
	DIR				*tmp_dir;
	struct dirent	*tmp_info;

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
	closedir(tmp_dir);
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
					if (ch_inin(rdr, group_head) == 1)
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
