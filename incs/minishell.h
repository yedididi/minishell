/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:58 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/17 12:26:28 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "parse.h"
# include "../get_next_line/get_next_line_bonus.h"

# define WHITESPACE "\t\n\v\f\r "
# define REDIRECTION "<>"
# define STDIN 0
# define STDOUT 1

int EXIT_STATUS;

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_minishell
{
    t_env_node	*env_head;
    t_group   *group_head;
}	t_minishell;

void	error();

void    rl_replace_line (const char *text, int clear_undo);

void	start_shell(t_minishell *minishell, char *envp[]);

void    init(int argc, char *argv[], char *envp[], t_minishell *minishell);
void	set_signal();
void    handler(int signum);

void    envp_to_list(char **envp, t_minishell *minishell);
char    *get_variable(char *envp);
char    *get_value(char *envp);

void	init_env_list(t_minishell *minishell);
t_env_node	*create_new_envnode(char *variable, char *value);
void	add_new_envnode(char *variable, char *value, t_env_node *env_head);
void	free_envnode(t_env_node *node);
t_env_node	*search_envnode(char *variable, t_env_node *env_head);

int	    is_whitespace(char *line);

void	execute(t_minishell *minishell);
void	execute_group(t_group *group);
void	execute_group_pipe(t_group *group);
void	end_input(t_group *group);

t_rdr	*find_input_rdr(t_group *group);
int		*find_output_rdr(t_group *group);
int		open_out(t_rdr *rdr, int type);

void	env(t_group *group);
void	export(t_env_node *env_head, t_wd *word);
void	export_equal(t_env_node *env_head, char *str, char *value, char *variable);
void	unset(t_env_node *env_head, char *variable);
void	pwd(void);

void	echo(t_group *group);
void	exiit(t_group *group);
void	cd(t_group *group, t_env_node *env_head);

void	execute_cmd(t_group *group);
void	execute_regular(t_group *group);
char	*get_cmd_path(char **path, char *cmd);
char	**get_option(t_group *group);

void	error_input(void);
int		str_find_chr(char *str, char c);
int		is_alpha_and_(char *str);
int		chk_equal_sign(char *str);

void	ft_parse(t_minishell *minishell, char **envp, char *line);
t_token	*ft_tokenizer(char *line);

int		ft_isspace(char ch);
char	*ft_strndup(char *src, int len);

t_list	*ft_newnode(char *data);
void	ft_lstadd(t_list **head, t_list *node);

void	heredoc(t_group	*group_head);
int	ch_outout(t_rdr *rdr);
void	fill_heredoc(t_rdr *rdr, int random_fd);

#endif
