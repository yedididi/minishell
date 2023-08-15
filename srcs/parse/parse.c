/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:16:56 by boran             #+#    #+#             */
/*   Updated: 2023/08/15 13:27:25 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
int	ft_quotelen(char *line, char quote)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != quote)
	{
//		if (ft_isspace(line[len]))
//			ft_error(command not found)
		++len;
	}
	if (!line[len])
		return (-1);
	return (len);
}
*/

void	ft_lexer(t_token **token, char *line)
{
}

t_token	*ft_tokenizer(char *line)
{
	t_token	*tokens;
	int		len;

	tokens = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			++line;
		else if (*line == '|')
		{
			ft_addtoken(&tokens, pipe_tkn, ft_strndup(line, 1));
			++line;
			if (*line == '|')
				return (tokens);
		}
		else if (*line == '<' || *line == '>')
		{
			len = 1;
			if (*(line + 1) == *line)
				++len;
			ft_addtoken(&tokens, redir_tkn, ft_strndup(line, len));
			line += len;
		}
		else
		{
			len = 0;
			while (line[len] && !ft_isspace(line[len]) && line[len] != '|' \
					&& line[len] != '<' && line[len] != '>')
				++len;
			ft_addtoken(&tokens, word_tkn, ft_strndup(line, len));
			line += len;
		}
	}
	return (tokens);
}

t_group	*ft_parser(t_token *tokens)
{
	t_token	*tmp;
	t_wd	*word;
	t_rdr	*redir;
	t_group	*groups;

	groups = NULL;
	while(tokens)
	{
		word = NULL;
		redir = NULL;
		while (tokens && tokens->type == word_tkn)
		{
			ft_addword(&word, tokens->data);
			tokens = tokens->next_tkn;
		}
		while (tokens && tokens->type != pipe_tkn)
		{
			if (tokens->type == redir_tkn)
			{
				if (tokens->next_tkn->type == word_tkn)
				{
					ft_addredir(&redir, tokens->data, tokens->next_tkn->data);
					tokens = tokens->next_tkn;
				}
				else
					ft_addredir(&redir, tokens->data, NULL);
				tokens = tokens->next_tkn;
			}
			else if (tokens->type == word_tkn)
			{
				ft_addword(&word, tokens->data);
				tokens = tokens->next_tkn;
			}
		}
		ft_addgroup(&groups, word, redir);
		if (tokens && tokens->type == pipe_tkn)
			tokens = tokens->next_tkn;
	}
	return (groups);
}

t_group  *parse(char *line, t_minishell *minishell)
{
	heredoc(minishell->group_head);
	ft_parser(ft_tokenizer(line));
}

//rdr을 돌면서 outout이 있는지 찾는다.

void	heredoc(t_group	*group_head)
{
	t_group	*group;
	t_rdr	*rdr;

	group = group_head;
	while (group)
	{
		rdr = group->rdr_head;
		while (rdr)
		{
			if (rdr->type == outout_rdr)
			{
				while (1)
				{
					if (ch_outout(rdr) == 1)
						break ;
				}
			}
			if (rdr == group->rdr_tail)
				break ;
			rdr = rdr->next_rdr;
		}
		group = group->next_group;
	}
}

//있으면 각 outout에 대해서 무작위랜덤이름 파일을 /tmp에 
//open(무작위랜덤이름, O_RDWR | O_CREAT | O_APPEND, 0644); 이렇게 만든다.
//만들기 전에 해당 파일 이름이 해당 디렉토리에 존재하는지 확인 필요.

int	ch_outout(t_rdr *rdr)
{
	char			random_name[8];
	int				random_fd;
	DIR				*tmp_dir;
	struct dirent	*tmp_info;
	char            *dir_file;
    int             i;

	i = 0;
	random_fd = open("/dev/urandom", O_RDONLY);
	if (read(random_fd, random_name, 8) == -1)
		error();
	close(random_fd);
	while (8 > i)
	{
		if (random_name[i] < 0)
			random_name[i] = random_name[i] * -1;
		random_name[i] = random_name[i] % 26 + 'a';
		i++;
	}
	rdr->filename = ft_strdup(random_name);
	tmp_dir = opendir("/tmp");
	tmp_info = readdir(tmp_dir);
	while (tmp_info)
	{
		if (ft_strncmp(random_name, tmp_info->d_name, 8) == 0)
		{
			closedir(tmp_dir);
			return (0);
		}
		tmp_info = readdir(tmp_dir);
	}
	dir_file = ft_strjoin("/tmp/", random_name);
	random_fd = open(dir_file, O_RDWR | O_CREAT | O_APPEND, 0644); //random file open
	free(dir_file);
	fill_herdoc(rdr, random_fd);
}

//만들고 나서 입력값 받아줘서 쓴다. gnl 로 하면 될듯.
//입력값 받는 도중에 시그널 (ctrl+dc) 들어올 것을 대비해서 fork로 프로세스 만들어서 해결해야할듯
//다 받으면 저장해주고 close해준다.
//후에 filename 아까 만든 무작위랜덤이름으로 바꾸고 type은 out으로 바꿔주면 끝

void	fill_heredoc(t_rdr *rdr, int random_fd)
{
	int		status;
	pid_t	pid;
	char *str;

	pid = fork();
	if (pid == 0)
	{
		str = get_next_line(0);
		while (str)
		{
			write(random_fd, str, ft_strlen(str));
			str = get_next_line(0);
		}
		close(random_fd);
		exit(0);
	}
	else if (pid == -1)
		error();
	waitpid(pid, &status, 0);
	EXIT_STATUS = WEXITSTATUS(status);
	close(random_fd);
	rdr->type = out_rdr;
}