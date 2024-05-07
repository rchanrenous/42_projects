/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:41:11 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 17:19:46 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	transition(t_game *game, t_parse *prs)
{
	game->scene.map = ft_strsdup(prs->map);
	game->scene.textures[NO] = ft_strdup(prs->no);
	game->scene.textures[SO] = ft_strdup(prs->so);
	game->scene.textures[EA] = ft_strdup(prs->ea);
	game->scene.textures[WE] = ft_strdup(prs->we);
	if (!game->scene.textures[0] || !game->scene.textures[1]
		|| !game->scene.textures[2] || !game->scene.textures[3]
		|| !game->scene.map)
	{
		free_parse(prs);
		perror("Malloc() transition() ");
		return (1);
	}
	game->scene.floor_color = prs->floor;
	game->scene.ceiling_color = prs->ceiling;
	free_parse(prs);
	return (0);
}
