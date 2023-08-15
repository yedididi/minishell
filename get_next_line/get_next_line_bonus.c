/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:12:46 by yejlee2           #+#    #+#             */
/*   Updated: 2022/12/08 11:50:42 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	nl_index(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*return_line(char **remainder)
{
	int		nl;
	char	*tmp;
	char	*return_this;
	char	*next_remain;

	nl = nl_index(*remainder);
	if (*remainder == 0)
		return (0);
	else if (nl >= 0)
	{
		return_this = ft_strndup(*remainder, nl + 1);
		next_remain = *remainder + nl + 1;
		tmp = ft_strndup(next_remain, ft_strlen(next_remain));
		free(*remainder);
		*remainder = tmp;
		return (return_this);
	}
	else
	{
		return_this = *remainder;
		*remainder = 0;
		free(*remainder);
	}
	return (return_this);
}

char	*nl_notfound(char **remainder, char *buf, int fd)
{
	int		byte;
	char	*tmp;

	while (nl_index(*remainder) == -1)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte <= 0)
			break ;
		buf[byte] = '\0';
		if (*remainder == 0)
			tmp = ft_strndup(buf, byte);
		else
			tmp = ft_strjoin(*remainder, buf);
		free(*remainder);
		*remainder = tmp;
	}
	if (byte == -1)
	{
		free(*remainder);
		*remainder = 0;
		return (0);
	}
	return (return_line(remainder));
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (0);
	if (nl_index(remainder[fd]) == -1)
		return (nl_notfound(&remainder[fd], buf, fd));
	else
		return (return_line(&remainder[fd]));
}
