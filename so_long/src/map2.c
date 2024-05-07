/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:19:41 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 16:36:29 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_free(char ***map)
{
	int	i;

	if (map == NULL || *map == NULL)
		return ;
	i = 0;
	while ((*map)[i] != NULL)
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

static void	map_fill_null(char **map, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		map[i] = NULL;
		i++;
	}
}

char	**map_duplicate(char **map)
{
	int		i;
	int		len;
	char	**res;
	char	*str;

	if (map == NULL)
		return (NULL);
	len = 0;
	while (map[len] != NULL)
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (res == NULL)
		return (NULL);
	map_fill_null(res, len + 1);
	i = 0;
	while (i < len)
	{
		str = ft_strdup(map[i]);
		if (str == NULL)
			return (map_free(&res), NULL);
		res[i] = str;
		i++;
	}
	return (res);
}
