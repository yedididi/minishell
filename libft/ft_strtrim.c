/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:07:33 by yejlee2           #+#    #+#             */
/*   Updated: 2022/11/23 11:40:31 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	get_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start])
	{
		if ((!is_set(s1[start], set)))
			break ;
		start++;
	}
	if (s1[start] == 0)
		return (-1);
	return (start);
}

int	get_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (s1[end])
	{
		if ((!is_set(s1[end], set)))
			break ;
		end--;
	}
	if (end == -1)
		return (-1);
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*fin_str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = get_start(s1, set);
	end = get_end(s1, set);
	if ((start == -1) && (end == -1))
		return (ft_strdup(""));
	fin_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (fin_str == 0)
		return (0);
	while (end >= start)
		fin_str[i++] = s1[start++];
	fin_str[i] = '\0';
	return (fin_str);
}
