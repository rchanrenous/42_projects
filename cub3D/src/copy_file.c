/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:05:33 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 16:25:58 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	supp_back_n(t_parse *prs, int i, char *tp)
{
	while (prs->file && prs->file[++i])
	{
		tp = ft_strtrim(prs->file[i], "\n");
		if (!tp)
			return (perror("Malloc() supp_back_n() "), 1);
		free(prs->file[i]);
		prs->file[i] = tp;
		tp = NULL;
		if (!prs->file)
			return (perror("Malloc() supp_back_n() "), 1);
	}
	return (0);
}

static int	copy_tmp(t_parse *prs, int i)
{
	if (prs->size > 0)
	{
		while (++i < prs->size)
		{
			prs->file[i] = ft_strdup(prs->tmp[i]);
			if (!prs->file[i])
				return (perror("Malloc() copy_tmp() "), 1);
		}
		free_strs(prs->tmp);
		prs->tmp = NULL;
	}
	prs->file[prs->size] = ft_strdup(prs->line);
	if (!prs->file[prs->size])
		return (perror("Malloc() copy_tmp() "), 1);
	prs->file[prs->size + 1] = NULL;
	return (0);
}

static int	copy_line(t_parse *prs, int i)
{
	prs->tmp = malloc(sizeof(char *) * (prs->size + 1));
	if (!prs->tmp)
		return (perror("Malloc() copy_line() "), 1);
	while (++i < prs->size)
	{
		prs->tmp[i] = ft_strdup(prs->file[i]);
		if (!prs->tmp[i])
			return (perror("Malloc() copy_line() "), 1);
	}
	prs->tmp[i] = NULL;
	free_strs(prs->file);
	prs->file = NULL;
	return (0);
}

static int	add_line(t_parse *prs)
{
	prs->size++;
	if (prs->size > 0)
		if (copy_line(prs, -1))
			return (1);
	prs->file = malloc(sizeof(char *) * (prs->size + 2));
	if (!prs->file)
		return (perror("Malloc() add_line() "), 1);
	if (copy_tmp(prs, -1))
		return (1);
	return (0);
}

int	copy_file(t_parse *prs, char *file, int ret)
{
	prs->fd = open(file, O_RDONLY);
	if (prs->fd < 0)
		return (perror(NULL), 1);
	while (1)
	{
		if (ret)
			prs->line = gnl(-1, prs->buff);
		else
			prs->line = gnl(prs->fd, prs->buff);
		if (!prs->line && ret > 0)
			return (close(prs->fd), ret);
		if (!prs->line && ret == 0)
			break ;
		ret = add_line(prs);
		free(prs->line);
		prs->line = NULL;
	}
	close(prs->fd);
	if (!prs->file)
		return (write(2, "Error\n Malloc() copy_file()\n", 28), 1);
	if (supp_back_n(prs, -1, NULL))
		return (1);
	return (0);
}
