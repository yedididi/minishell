/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:34:56 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/15 14:07:30 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	env(t_group *group)
{
	t_env_node	*node;

	node = group->env_head->next_node; //env 인자가 들어왔을 때 예외처리
	if (group->wd_head->next_wd)
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(group->wd_head->next_wd->word, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	while (1)
	{
		ft_putstr_fd(node->variable, 1);
		write(1, "=", 1);
		ft_putstr_fd(node->value, 1);
		write(1, "\n", 1);
		if (node->next_node == 0)
			break ;
		node = node->next_node;
	}
}

void	export(t_env_node *env_head, t_wd *wd)
{
	while (wd)
	{
		// if (!chk_equal_sign(wd->word) && is_alpha_and_(wd->word)) //등호가 없고 영문자 및 _ 로 구성이 되었다면 뛰어넘기
		// 	wd = wd->next_wd;
		if (!chk_equal_sign(wd->word) && !is_alpha_and_(wd->word)) //등호가 없고 숫자 및 특수기호로만 구성되어있다면 에러문구
			error_input();
		else if (chk_equal_sign(wd->word)) //등호가 있으면 적용
			export_equal(env_head, wd->word);
		wd = wd->next_wd;
	}
}

void	export_equal(t_env_node *env_head, char *str)
{
	char *variable;
	char *value;
	int	i;

	i = 0;
	if (*str != '_' && !ft_isalpha(*str)) //첫번째 문자가 영문자나 _가 아니면 에러문구+끝
		error_input();
	variable = (char *)malloc(sizeof(char) * (str_find_chr(str, '=') + 1));
	value = (char *)malloc(sizeof(char) * (ft_strlen(str) - str_find_chr(str, '=')));
	if (variable == 0 && value == 0)
		error_input();
	while (*str != '=')
	{
		if (ft_isalnum(*str) && *str == '_')
			variable[i++] = *str;
		else
			error_input(); //variable, value 모두 free 해주고 오류메세지 출력 후 line으로 돌아가기
		str++;
	}
	variable[i] = '\0';
	str++;
	i = 0;
	while (*str)
	{
		value[i++] = *str;
		str++;
	}
	value[i] = '\0';
	add_new_envnode(variable, value, env_head);
}

void	unset(t_env_node *env_head, char *variable)
{
	t_env_node	*node;
	
	node = env_head;
	while (node)
	{
		if (ft_strncmp(variable, node->next_node->variable, ft_strlen(variable)) == 0)
		{
			node->next_node = node->next_node->next_node;
			free_envnode(node->next_node);
			return ;
		}
		node = node->next_node;
	}
	//no error statement when there is no variable
}

void	pwd(void)
{
	char cwd[256];

   	if (getcwd(cwd, sizeof(cwd)))
    	ft_putstr_fd(cwd, 1);
	else
       	error();
}

void	cd(char *dirname, t_env_node *env_head)
{
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	if (chdir(dirname) == 1)
	{
		//print error statement
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(dirname, 1);
		ft_putstr_fd(": No such file or directory", 1);
	}
	else
	{
		//change OLDPWD, PWD
		oldpwd = search_envnode("OLDPWD", env_head);
		pwd = search_envnode("PWD", env_head);
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = dirname;
	}
}
