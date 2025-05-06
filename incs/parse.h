/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:03:28 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/29 13:54:53 by boran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>

# define WHITESPACE "\t\n\v\f\r "

# define ALLO 0
# define SNTX 1
# define PIPE 2

enum	e_token_type
{
	word_tkn,
	redir_tkn,
	pipe_tkn,
};

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next_tkn;
}	t_token;

typedef struct s_wd
{
	char		*word;
	char		*expanded;
	struct s_wd	*next_wd;
}	t_wd;

enum e_rdr_type
{
	in_rdr,
	out_rdr,
	inin_rdr,
	outout_rdr,
};

typedef struct s_rdr
{
	int				type;
	char			*filename;
	char			*expanded;
	char			*stop_str;
	int				fd;
	struct s_rdr	*prev_rdr;
	struct s_rdr	*next_rdr;
}	t_rdr;

typedef struct s_env_node
{
	char				*variable;
	char				*value;
	struct s_env_node	*next_node;
}	t_env_node;

typedef struct s_group
{
	t_wd			*wd_head;
	t_rdr			*rdr_head;
	t_rdr			*rdr_tail;
	int				pipe[2];
	pid_t			pid;
	int				out_len;
	int				in_len;
	int				in_err;
	int				heredoc_stop;
	int				ctrl;
	char			*home;
	char			**envp;
	t_env_node		*env_head;
	t_env_node		*env_tail;
	struct s_group	*prev_group;
	struct s_group	*next_group;
}	t_group;

t_token	*ft_tokenizer(char *line);
t_group	*ft_parser(t_token *tokens);
void	ft_remove_dollar_before_closed_quote(t_group *groups);
void	ft_expansion(t_group *groups);
void	ft_expand_exit_status(t_group *groups);
void	ft_remove_quote(t_group *groups);

void	ft_addtoken(t_token **head, int type, char *data);
void	ft_addword(t_wd **head, t_token *token);
void	ft_addredir(t_rdr **head, t_token *token_rdr, t_token *token_file);
void	ft_addgroup(t_group **head, t_wd *word, t_rdr *redir);

int		ft_isspace(char ch);
int		ft_issymbol(char ch);
char	*ft_strndup(char *src, int len);
int		ft_strcmp(char *str1, char *str2);
void	*ft_free(void *ptr);

int		ft_is_invalid(t_token *tokens);
void	ft_check_rdr_valid(t_group *groups);
t_token	*ft_next_token(t_token **token, int ishead);
void	ft_cleartkn(t_token **tokens);
int		ft_error(int errno, char *errstr);

char	*ft_replace(char **str, int key_range[2], \
		t_env_node *env, int value_len);
char	*ft_replace_env(char *expanded, char **str, int start, t_env_node *env);
char	*ft_update_expanded(char *expanded, char *str, int start, int len);

int		ft_quote_pos(char *str, int first);

#endif
