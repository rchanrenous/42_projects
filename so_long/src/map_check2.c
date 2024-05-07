/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:27:09 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 14:57:27 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_valid_char(char m, int *p, int *e)
{
	if (m != '1' && m != '0' && m != 'C' && m != 'P' && m != 'E')
		return (0);
	if (m == 'E')
		(*e)++;
	if (m == 'P')
		(*p)++;
	return (1);
}

int	line_is_wall(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	line_is_intermediate(char *line)
{
	static int	e = 0;
	static int	p = 0;

	if (*line == '\0' || *line != '1')
		return (0);
	line++;
	while (*line != '\0' && *(line + 1) != '\0')
	{
		if (map_valid_char(*line, &p, &e) == 0)
			return (0);
		line++;
	}
	if (*line != '1')
		return (0);
	return (1);
}
