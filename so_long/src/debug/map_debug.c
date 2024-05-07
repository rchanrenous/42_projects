/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:47:39 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/10 11:32:57 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_print_raw(char **map)
{
	if (map == NULL)
		return ;
	while (*map != NULL)
	{
		ft_printf("%s\n", *map);
		map++;
	}
}

void	map_print(char **map)
{
	if (map == NULL)
		return ;
	while (*map != NULL && ft_strlen(*map) != 0)
	{
		ft_printf("%s\n", *map);
		map++;
	}
}
