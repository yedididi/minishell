/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:34:31 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/13 16:48:53 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	execute_cmd(t_group *group)
{
	if (ft_strncmp("echo\0", group->wd_head->word, 5) == 0)
		echo(group);
	else if (ft_strncmp("cd\0", group->wd_head->word, 3) == 0)
		cd(group->wd_head->next->word, group->env_head);
	else if (ft_strncmp("pwd\0", group->wd_head->word, 4) == 0)
		pwd();
	else if (ft_strncmp("export\0", group->wd_head->word, 7) == 0)
		export(group->env_head, group->wd_head->next->word);
	else if (ft_strncmp("unset\0", group->wd_head->word, 6) == 0)
		unset(group->env_head, group->wd_head->next->word);
	else if (ft_strncmp("env\0", group->wd_head->word, 4) == 0)
		env(group);
	else if (ft_strncmp("exit\0", group->wd_head->word, 5) == 0)
		exiit();
	else
		execute_regular(group);
}

void	execute_regular(t_group *group)
{
	char	*path;
	char	**sp_path;
	char	*cmd_path;
	char	**option;

	ft_memset(&path, 0, 1);
	while (*(group->envp))
	{
		if (ft_strncmp("PATH=", *(group->envp), 5) == 0)
		{
			path = *(group->envp) + 5;
			break ;
		}
		group->envp++;
	}
	sp_path = ft_split(path, ':');
	cmd_path = get_cmd_path(sp_path, group->wd_head->word);
	option = get_option(group);
	execve(cmd_path, option, group->envp);
	// free_double(sp_path);
	// free_double(option);
	free(cmd_path);
}

char	*get_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*str;
	int		fd;
	char	*temp;

	i = 0;
	temp = ft_strjoin("/", cmd);
	free(cmd);
	cmd = temp;
	while (path[i])
	{
		str = ft_strjoin(path[i], cmd);
		fd = access(str, X_OK);
		if (fd != -1)
		{
			free(cmd);
			return (str);
		}
		free(str);
		i++;
	}
	free(cmd);
	//에러문구출력
	error_input();
	return (NULL);
}

char	**get_option(t_group *group)
{
	char	**option;
	t_wd	*wd;
	int		wd_len;
	int 	i;

	wd_len = 0;
	i = 0;
	wd = group->wd_head;
	while (wd)
	{
		wd_len++;
		wd = wd->next;
	}
	option = (char **)malloc(sizeof(char *) * (wd_len + 1));
	if (option == 0)
		error_input();
	wd = group->wd_head;
	while (wd)
	{
		option[i] = wd->word;
		wd = wd->next;
		i++;
	}
	option[i] = NULL;
	return (option);
}