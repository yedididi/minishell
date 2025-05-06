/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 10:05:47 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/28 15:44:41 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	is_executable(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd != -1 && ft_strncmp(file_name, "./", 2) == 0)
	{
		ft_printf_err("minishell: %s: Permission denied\n", file_name);
		close(fd);
		exit(126);
	}
	if (ft_strncmp(file_name, "/", 1) == 0)
	{
		ft_printf_err("minishell: %s: No such file or directory\n", file_name);
		close(fd);
		exit(127);
	}
	if (fd != -1)
	{
		ft_printf_err("minishell: %s: command not found\n", file_name);
		close(fd);
		exit(127);
	}
}

void	is_directory(char *dir_name)
{
	DIR	*tmp_dir;

	tmp_dir = opendir(dir_name);
	if (tmp_dir != NULL && (ft_strncmp(dir_name, "./", 2) == 0 || \
		ft_strncmp(dir_name, "/", 1) == 0))
	{
		closedir(tmp_dir);
		ft_printf_err("minishell: %s: is a directory\n", dir_name);
		exit(126);
	}
	if (ft_strncmp(dir_name, "/", 1) == 0)
	{
		ft_printf_err("minishell: %s: No such file or directory\n", dir_name);
		exit(127);
	}
	if (tmp_dir != NULL)
	{
		closedir(tmp_dir);
		ft_printf_err("minishell: %s: command not found\n", dir_name);
		exit(127);
	}
}

void	is_file(char *word)
{
	if (ft_strncmp(word, "/bin", 4) == 0 || ft_strncmp(word, "/sbin", 5) == 0 \
		|| ft_strncmp(word, "/usr/bin", 8) == 0 || \
		ft_strncmp(word, "/usr/sbin", 9) == 0 || \
		ft_strncmp(word, "/usr/local/bin", 14) == 0 || \
		ft_strncmp(word, "/usr/local/sbin", 15) == 0)
		return ;
	is_directory(word);
	if (ft_strncmp(word, "./", 2) == 0 && access(word, X_OK) == 0)
	{
		printf("it is executable\n");
		return ;
	}
	is_executable(word);
	if (ft_strncmp(word, "./", 2) == 0 || ft_strncmp(word, "/", 1) == 0)
	{
		ft_printf_err("minishell: %s: No such file or directory\n", word);
		exit(127);
	}
	if (ft_strncmp(word, "\0", ft_strlen(word)) == 0)
	{
		ft_printf_err("minishell: %s: command not found\n", word);
		exit(127);
	}
}

int	*dup_out_fd(t_group *group)
{
	int	*out_fd;

	if (group->out_len == 0)
		return (NULL);
	out_fd = find_output_rdr(group);
	if (out_fd == NULL)
		exit(1);
	dup2(out_fd[group->out_len], STDOUT);
	return (out_fd);
}

int	*dup_in_fd(t_group *group)
{
	int	*in_fd;

	if (group->in_len == 0)
		return (NULL);
	in_fd = find_input_rdr(group);
	if (in_fd == NULL)
		exit(1);
	dup2(in_fd[group->in_len], STDIN);
	return (in_fd);
}
