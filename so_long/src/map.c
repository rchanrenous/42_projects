/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:49:08 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/17 15:32:29 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* does not free in case of error! (helps freeing when extend is called))*/
static int	map_fill(char ***map, int size)
{
	int	i;

	if (size < 1)
		return (0);
	i = 0;
	while (i < size)
	{
		(*map)[i] = malloc(sizeof(char));
		if ((*map)[i] == NULL)
			return (0);
		(*map)[i][0] = '\0';
		i++;
	}
	(*map)[size] = NULL;
	return (1);
}

static int	map_init(char ***map)
{
	if (map == NULL)
		return (0);
	*map = malloc(sizeof(char *) * (MAP_INIT_SIZE + 1));
	if (*map == NULL)
		return (0);
	if (map_fill(map, MAP_INIT_SIZE) == 0)
	{
		map_free(map);
		return (0);
	}
	return (1);
}

static void	map_copy(char **src, char **dst, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

static int	map_extend(char ***map)
{
	static int	k = 2;
	char		**new;
	char		**tmp;

	new = malloc(sizeof(char *) * (k * MAP_INIT_SIZE + 1));
	if (new == NULL)
	{
		map_free(map);
		return (0);
	}
	map_copy(*map, new, (k - 1) * MAP_INIT_SIZE);
	tmp = new + (k - 1) * MAP_INIT_SIZE;
	*tmp = NULL;
	if (map_fill(&tmp, MAP_INIT_SIZE) == 0)
	{
		map_free(&new);
		free(*map);
		map = NULL;
		return (0);
	}
	k++;
	free(*map);
	*map = new;
	return (1);
}

int	map_append_line(char ***map, char *str)
{
	static int	next_empty = 0;

	if (map == NULL)
		return (0);
	if (*map == NULL)
	{
		if (map_init(map) == 0)
			return (0);
	}
	if ((*map)[next_empty] == NULL)
	{
		if (map_extend(map) == 0)
			return (0);
	}
	free((*map)[next_empty]);
	(*map)[next_empty] = str;
	next_empty++;
	return (1);
}
