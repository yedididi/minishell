/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:12:46 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/26 16:05:52 by yejlee2          ###   ########.fr       */
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
		return_this = ft_strnndup(*remainder, nl + 1);
		next_remain = *remainder + nl + 1;
		tmp = ft_strnndup(next_remain, ft_strlen(next_remain));
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
			tmp = ft_strnndup(buf, byte);
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

// char	*get_next_line(int fd)
// {
// 	char	*buf;
// 	char	c;
// 	int		i;
// 	int		ret;

// 	i = 0;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (buf == NULL)
// 		return (NULL);
// 	ret = read(fd, &c, 1);
// 	while (ret > 0)
// 	{
// 		buf[i++] = c;
// 		if (c == '\n')
// 			break ;
// 		ret = read(fd, &c, 1);
// 	}
// 	if (ret <= 0 && i == 0)
// 	{
// 		free(buf);
// 		return (NULL);
// 	}
// 	buf[i] = '\0';
// 	return (buf);
// }
