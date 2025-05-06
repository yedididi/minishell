/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:58 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 16:12:05 by yejlee2          ###   ########.fr       */
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
# include "../get_next_line/ft_printf.h"

# define WHITESPACE "\t\n\v\f\r "
# define STDIN 0
# define STDOUT 1

int	g_exit_status;

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_minishell
{
	char		*home;
	t_env_node	*env_head;
	t_env_node	*env_tail;
	t_group		*group_head;
}	t_minishell;

void		rl_replace_line(const char *text, int clear_undo);

void		start_shell(t_minishell *minishell, char *envp[]);
void		print_exit(void);

void		init(int argc, char *envp[], t_minishell *minishell);
void		set_signal(void);
void		handler(int signum);

void		envp_to_list(char **envp, t_minishell *minishell);
char		*get_variable(char *envp);
char		*get_value(char *envp);
void		change_envnode(char *variable, char *value, t_env_node *env_head);

void		init_env_list(t_minishell *minishell);
t_env_node	*create_new_envnode(char *variable, char *value);
void		add_new_envnode(char *variable, char *value, t_env_node *env_tail);
void		free_envnode(t_env_node *node);
t_env_node	*search_envnode(char *variable, t_env_node *env_head);

int			is_whitespace(char *line);

void		execute(t_minishell *minishell);
int			execute_group(t_group *group);
int			execute_group_pipe(t_group *group);
void		end_input(t_group *group);

int			fork_for_pipe(t_group *group);
void		rdr_child(t_group *group);
void		fd_close(t_group *group, int *out_fd, int *in_fd);

void		get_rdr_len(t_group *group);
int			*find_input_rdr(t_group *group);
int			open_in(t_rdr *rdr);
int			*dup_out_fd(t_group *group);
int			*dup_in_fd(t_group *group);

int			*get_int_malloc(int size);
int			*find_output_rdr(t_group *group);
int			open_out(t_rdr *rdr, int type);

int			exportt(t_env_node *env_head, t_wd *word);
int			export_equal(t_env_node *env_head, char *str);
int			export_error(char *str);
void		print_export(t_env_node *env_head);
char		**sort_export(t_env_node *env_head);
char		**ascii_sort(t_env_node *env_head, char **arr);
char		*cut_variable(char *str);
char		*cut_value(char *str);

int			get_env_len(t_env_node *env_head);
int			unset(t_env_node *env_head, t_wd *wd);
void		unset_this(t_env_node *env_head, char *variable);
int			env(t_group *group);

int			pwd(void);
void		echo(t_group *group);
int			is_option_n(char *str);
int			exiit(t_group *group);
void		exit_branch(char *word);
int			cd(t_group *group, t_env_node *env_head);
char		*get_dirname(t_group *group, t_env_node *env_head);
void		change_pwd(t_env_node *pwd, t_env_node *oldpwd);

int			execute_cmd(t_group *group);
int			execve_cmds(t_group *group);
void		execute_regular(t_group *group);
void		no_file_dir_err(char *str);
char		*get_cmd_path(char **path, char *cmd);
char		**get_option(t_group *group);

int			str_find_chr(char *str, char c);
int			is_alpha_and_(char *str);
int			chk_equal_sign(char *str);
int			ft_isspecial(char *str);

void		free_double_char(char **str);
int			isnumber_str(char *str);
int			over_longlong(char *str);
long long	ft_atol(char *str);
void		is_executable(char *file_name);
void		is_directory(char *dir_name);
void		is_file(char *word);

void		fork_fail(void);
void		malloc_fail(void);
void		pipe_fail(void);
void		read_fail(void);

void		ft_parse(t_minishell *minishell, char **envp, char *line);

int			ft_isspace(char ch);
char		*ft_strndup(char *src, int len);

t_list		*ft_newnode(char *data);
void		ft_lstadd(t_list **head, t_list *node);

void		heredoc(t_group	*group_head);
int			ch_inin(t_rdr *rdr, t_group	*group_head);
int			fill_heredoc(t_rdr *rdr, int random_fd);
void		heredoc_child(t_rdr *rdr, int random_fd);
int			chk_for_dup_file(char *random_name);
char		*make_random_file(void);

void		free_input(t_group *group_head);
void		free_wd(t_wd *wd_head);
void		free_rdr(t_rdr *rdr_head);

#endif
