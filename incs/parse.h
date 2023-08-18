/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:03:28 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/18 11:12:03 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>

# define WHITESPACE "\t\n\v\f\r "

enum	e_token_type
{
	word_tkn,
	redir_tkn,
	pipe_tkn,
} t_token_type;

// linked list
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next_tkn;
}	t_token;

// linked list
typedef struct s_wd
{
	char		*word;
	struct s_wd	*next_wd;
}	t_wd;

enum e_rdr_type
{
	in_rdr,		// < : 0
	out_rdr,	// > : 1
	inin_rdr,	// << : 2
	outout_rdr,	// >> : 3
} t_rdr_type;

typedef struct s_rdr //원형
{
	int				type;	// IN_RDR, OUT_RDR, ININ_RDR, OUTOUT_RDR
	char			*filename;
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

typedef struct s_group //원형아님
{
	t_wd			*wd_head;	// head : command, others : option & path
	t_rdr			*rdr_head;
	t_rdr			*rdr_tail;
	int				pipe[2]; //-1로 초기화
	pid_t			pid; //NULL로 초기화
	int				out_len; //0 init
	char			**envp; //main에서 받은 envp 값 그대로 넣으면 됨
	t_env_node		*env_head; //minishell 구조체에 있는 값 그대로 넣으면 됨
	struct s_group	*prev_group;
	struct s_group	*next_group;
}	t_group;

// return NULL when error occurs
t_token	*ft_tokenizer(char *line);
t_group	*ft_parser(t_token *tokens);

int		ft_isspace(char ch);
char	*ft_strndup(char *src, int len);
int		ft_strcmp(char *str1, char *str2);
int		ft_is_invalid(t_token *tokens);

// return 0 when error occurs
int		ft_addtoken(t_token **head, int type, char *data);
int		ft_addword(t_wd **head, char *data);
t_rdr	*ft_newredir(char *redir, char *filename);
int		ft_addredir(t_rdr **head, char *redir, char *filename);
int		ft_addgroup(t_group **head, t_wd *word, t_rdr *redir);

#endif