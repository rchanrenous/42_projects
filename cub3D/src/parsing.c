/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:36:17 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/21 15:10:13 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_parse(t_parse *prs)
{
	prs->state = 1;
	prs->size = -1;
	prs->index = 0;
	prs->player = 0;
	prs->floor = -1;
	prs->ceiling = -1;
	prs->fd = 0;
	prs->file = NULL;
	prs->tmp = NULL;
	prs->line = NULL;
	prs->map = NULL;
	prs->no = NULL;
	prs->so = NULL;
	prs->we = NULL;
	prs->ea = NULL;
	prs->buff = malloc(4096);
	if (!prs->buff)
		return (perror("Malloc() init_parse() "), 1);
	return (0);
}

int	parsing(t_game *game, t_parse *prs, int ac, char **av)
{
	if (check_argv(ac, av) || init_parse(prs))
		return (1);
	if (copy_file(prs, av[1], 0))
		return (free_parse(prs), 1);
	if (parse_param(prs, -1, NULL) || parse_map(prs))
		return (free_parse(prs), 1);
	if (transition(game, prs))
		return (1);
	return (0);
}
