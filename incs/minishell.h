/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:58 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 11:23:39 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct  s_env_node
{
    char    *variable;
    char    *value;
    struct  s_env_node  *next_node;
} t_env_node;

typedef struct s_minishell
{
    t_env_node	*env_head;

}	t_minishell;

#define WHITESPACE "\t\n\v\f\r "
#define REDIRECTION "<>"

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

void	error();

void    rl_replace_line (const char *text, int clear_undo);

void	start_shell(void);

void    init(int argc, char *argv[], char *envp[], t_minishell *minishell);
void	set_signal();
void    handler(int signum);

void    envp_to_list(char **envp, t_minishell *minishell);
char    *get_variable(char *envp);
char    *get_value(char *envp);

void	init_env_list(t_minishell *minishell);
t_env_node	*create_new_envnode(char *variable, char *value);
void	add_new_envnode(char *variable, char *value, t_minishell *minishell);
void	free_envnode(t_env_node *node);

int	    is_whitespace(char *line);

void	execute();

t_list	*ft_tokenize(char *line);

int	ft_isspace(char ch);
char	*ft_strndup(char *src, int len);

t_list	*ft_newnode(char *data);
void	ft_lstadd(t_list **head, t_list *node);

#endif