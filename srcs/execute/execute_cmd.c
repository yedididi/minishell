/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:34:31 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 16:12:55 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	execute_cmd(t_group *group)
{
	if (ft_strncmp("echo\0", group->wd_head->word, 5) == 0)
		echo(group);
	else if (ft_strncmp("cd\0", group->wd_head->word, 3) == 0)
		return (cd(group, group->env_head->next_node));
	else if (ft_strncmp("pwd\0", group->wd_head->word, 4) == 0)
		return (pwd());
	else if (ft_strncmp("export\0", group->wd_head->word, 7) == 0)
		return (exportt(group->env_head->next_node, group->wd_head->next_wd));
	else if (ft_strncmp("unset\0", group->wd_head->word, 6) == 0)
		return (unset(group->env_head, group->wd_head->next_wd));
	else if (ft_strncmp("env\0", group->wd_head->word, 4) == 0)
		return (env(group));
	else if (ft_strncmp("exit\0", group->wd_head->word, 5) == 0)
		return (exiit(group));
	else
	{
		g_exit_status = execve_cmds(group);
		return (g_exit_status);
	}
	return (0);
}

int	execve_cmds(t_group *group)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		execute_regular(group);
	waitpid(pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT && group->ctrl == -1)
		ft_printf_err("^C\n");
	else if (WTERMSIG(status) == SIGQUIT && group->ctrl == -1)
		ft_printf_err("^\\Quit: 3\n");
	return (g_exit_status);
}

void	execute_regular(t_group *group)
{
	char	*path;
	char	**sp_path;
	char	*cmd_path;
	char	**option;
	int		ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	is_file(group->wd_head->word);
	ft_memset(&path, 0, 1);
	if (search_envnode("PATH", group->env_head->next_node) != NULL)
		path = search_envnode("PATH", group->env_head->next_node)->value;
	else
		no_file_dir_err(group->wd_head->word);
	sp_path = ft_split(path, ':');
	cmd_path = get_cmd_path(sp_path, group->wd_head->word);
	option = get_option(group);
	ret = execve(cmd_path, option, group->envp);
	free_double_char(sp_path);
	free_double_char(option);
	free(cmd_path);
	if (ret == -1)
		ret = 127;
	exit(ret);
}

char	*get_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*str;
	int		fd;
	char	*temp;

	i = 0;
	if (access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	temp = ft_strjoin("/", cmd);
	while (path[i])
	{
		str = ft_strjoin(path[i], temp);
		fd = access(str, X_OK);
		if (fd != -1)
		{
			free(temp);
			return (str);
		}
		free(str);
		i++;
	}
	free(temp);
	ft_printf_err("minishell: %s: command not found\n", cmd);
	exit(127);
	return (NULL);
}

char	**get_option(t_group *group)
{
	char	**option;
	t_wd	*wd;
	int		wd_len;
	int		i;

	wd_len = 0;
	i = 0;
	wd = group->wd_head;
	while (wd)
	{
		wd_len++;
		wd = wd->next_wd;
	}
	option = (char **)malloc(sizeof(char *) * (wd_len + 1));
	if (option == 0)
		malloc_fail();
	wd = group->wd_head;
	while (wd)
	{
		option[i] = wd->word;
		wd = wd->next_wd;
		i++;
	}
	option[i] = NULL;
	return (option);
}
