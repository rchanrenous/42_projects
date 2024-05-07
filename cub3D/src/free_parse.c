/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 23:08:04 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/21 15:10:19 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_parse_map(t_parse *prs)
{
	int	i;

	i = 0;
	while (i <= prs->size)
	{
		if (prs->map[i])
			free(prs->map[i]);
		i++;
	}
	free(prs->map);
}

void	free_parse(t_parse *prs)
{
	if (prs->line)
		free(prs->line);
	if (prs->buff)
		free(prs->buff);
	if (prs->no)
		free(prs->no);
	if (prs->so)
		free(prs->so);
	if (prs->we)
		free(prs->we);
	if (prs->ea)
		free(prs->ea);
	if (prs->file)
		free_strs(prs->file);
	if (prs->tmp)
		free_strs(prs->tmp);
	if (prs->map)
		free_parse_map(prs);
}
