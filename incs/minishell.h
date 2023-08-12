/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:58 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/12 16:36:10 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define WHITESPACE "\t\n\v\f\r "
#define REDIRECTION "<>"
#define	STDIN	0
#define	STDOUT	1

typedef enum    e_rdr_type
{
    IN_RDR, //< 0
    OUT_RDR, //> 1
    ININ_RDR, //<< 2
    OUTOUT_RDR, //>> 3
} t_rdr_type;

typedef struct  s_env_node
{
    char    *variable;
    char    *value;
    struct  s_env_node  *next_node;
} t_env_node;
 
typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_wd
{
    char    *words;
    struct s_wd *next_wd;
} t_wd;

typedef struct s_rdr
{
    int type; //> < >> <<
    char *filename;
	int				fd;
    struct s_rdr    *next_rdr;
	struct s_rdr    *prev_rdr;
}   t_rdr;

typedef struct s_group
{
    t_wd            *wd_head;
    t_rdr           *rdr_head;
	t_rdr           *rdr_tail;
    int             pipe[2]; //-1로 초기화
	pid_t			pid; //NULL로 초기화
    struct s_group	*prev_group;
    struct s_group	*next_group;
}   t_group;

typedef struct s_minishell
{
    t_env_node	*env_head;
    t_group   *group_head;
}	t_minishell;

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