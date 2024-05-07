/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 06:57:05 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 16:23:49 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*my_strdup(char *s)
{
	char	*dest;
	int		i;
	int		len;

	i = -1;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = s[i];
	return (dest);
}

static char	*my_substr(char *s, int start, int end)
{
	char	*dest;
	int		i;

	if (!s)
		return (NULL);
	dest = malloc(end - start + 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < end - start)
		dest[i] = s[start + i];
	dest[i] = '\0';
	return (dest);
}

static char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*dest;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (my_strdup(s2));
	if (!s2)
		return (my_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = malloc(len_s1 + len_s2 + 1);
	if (!dest)
		return (NULL);
	while (++i < len_s1)
		dest[i] = s1[i];
	while (++j < len_s2)
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	return (dest);
}

static char	*stop_read(char **next)
{
	int		n;
	char	*line;
	char	*tp;

	line = NULL;
	tp = NULL;
	n = find_back_n(*next);
	if (n == -1)
		line = my_strdup(*next);
	else
	{
		line = my_substr(*next, 0, n + 1);
		tp = my_strdup(&(*next)[n + 1]);
	}
	if (*next)
		free(*next);
	*next = my_strdup(tp);
	free(tp);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*gnl(int fd, char *buff)
{
	static char	*next = NULL;
	char		*line;
	char		*tp;
	int			size;

	size = 1;
	tp = NULL;
	if ((fd < 0 || !buff) && !next)
		return (NULL);
	if ((fd < 0 || !buff) && next)
		return (free(next), NULL);
	while (size > 0 && find_back_n(next) == -1)
	{
		size = read(fd, buff, 4095);
		buff[size] = '\0';
		tp = next;
		next = my_strjoin(tp, buff);
		if (tp)
			free(tp);
	}
	line = stop_read(&next);
	if (!line)
		free(next);
	return (line);
}
