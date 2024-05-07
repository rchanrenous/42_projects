/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:52:28 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 17:15:34 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clean_line(t_parse *prs, int i)
{
	int		x;
	int		size;
	char	*tmp;

	x = -1;
	tmp = NULL;
	size = ft_strlen(prs->map[i]);
	tmp = ft_strdup(prs->map[i]);
	if (!tmp)
		return (perror("Malloc() clean_line()"), 1);
	free(prs->map[i]);
	prs->map[i] = malloc(prs->size_line + 1);
	if (!prs->map[i])
		return (free(tmp), perror("Malloc() clean_line()"), 1);
	while (++x < prs->size_line)
	{
		if (x >= size || tmp[x] == ' ')
			prs->map[i][x] = '1';
		else
			prs->map[i][x] = tmp[x];
	}
	prs->map[i][x] = '\0';
	free(tmp);
	return (0);
}

int	clean_map_line(t_parse *prs)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	prs->size_line = 0;
	while (prs->map[++i])
	{
		size = ft_strlen(prs->map[i]);
		if (size > prs->size_line)
			prs->size_line = size;
	}
	i = -1;
	while (prs->map[++i])
	{
		if (clean_line(prs, i))
			return (1);
	}
	return (0);
}
