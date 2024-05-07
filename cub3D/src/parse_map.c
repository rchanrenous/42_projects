/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:04:17 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 16:41:52 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_tmp(t_parse *prs, int i, char *line)
{
	if (prs->size > 0)
	{
		while (++i < prs->size)
		{
			prs->map[i] = ft_strdup(prs->tmp[i]);
			if (!prs->map[i])
				return (perror("Malloc() copy_tmp() "), 1);
		}
		free_strs(prs->tmp);
		prs->tmp = NULL;
	}
	prs->map[prs->size] = ft_strdup(line);
	if (!prs->map[prs->size])
		return (perror("Malloc() copy_tmp() "), 1);
	prs->map[prs->size + 1] = NULL;
	return (0);
}

static int	copy_line(t_parse *prs, int i)
{
	prs->tmp = malloc(sizeof(char *) * (prs->size + 1));
	if (!prs->tmp)
		return (perror("Malloc() copy_line() "), 1);
	while (++i < prs->size)
	{
		prs->tmp[i] = ft_strdup(prs->map[i]);
		if (!prs->tmp[i])
			return (perror("Malloc() copy_line() "), 1);
	}
	prs->tmp[i] = NULL;
	free_strs(prs->map);
	prs->map = NULL;
	return (0);
}

static int	add_line(t_parse *prs, char *line)
{
	prs->size++;
	if (prs->size > 0)
		if (copy_line(prs, -1))
			return (1);
	prs->map = malloc(sizeof(char *) * (prs->size + 2));
	if (!prs->map)
		return (perror("Malloc() add_line() "), 1);
	if (copy_tmp(prs, -1, line))
		return (1);
	return (0);
}

int	parse_map(t_parse *prs)
{
	int	i;

	i = prs->size + 1;
	prs->size = -1;
	while (prs->file[i] && !prs->file[i][0])
		i++;
	if (!prs->file[i])
		return (write(2, "Error.\nMap is missing.\n", 23));
	while (prs->file[i] && prs->file[i][0])
	{
		if (add_line(prs, prs->file[i]))
			return (1);
		i++;
	}
	while (prs->file[i] && !prs->file[i][0])
		i++;
	if (prs->file[i])
		return (write(2, "Error.\nEmpty line in map.\n", 26));
	if (check_map(prs))
		return (1);
	return (0);
}
