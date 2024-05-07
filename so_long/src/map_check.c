/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:31 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 14:51:38 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_find(char **map, char c, int *i, int *j)
{
	*i = 0;
	while (map[*i] != NULL)
	{
		*j = 0;
		while (map[*i][*j] != '\0')
		{
			if (map[*i][*j] == c)
				return ;
			(*j)++;
		}
		(*i)++;
	}
	*i = -1;
	*j = -1;
}

static int	map_exists_exit(char **map, int i, int j)
{
	int	res;

	if (map[i][j] == '1')
		return (0);
	if (map[i][j] == 'E')
		return (map[i][j] = '1', 1);
	map[i][j] = '1';
	res = 0;
	res += map_exists_exit(map, i + 1, j);
	res += map_exists_exit(map, i - 1, j);
	res += map_exists_exit(map, i, j + 1);
	res += map_exists_exit(map, i, j - 1);
	return (res);
}

static int	map_valid_game(char **map)
{
	int		i;
	int		j;
	int		res;
	char	**map_dup;

	map_find(map, 'P', &i, &j);
	map_dup = map_duplicate(map);
	if (map_dup == NULL)
		return (ft_printf("Error\n"), 0);
	res = map_exists_exit(map_dup, i, j);
	map_free(&map_dup);
	if (res == 0)
		return (ft_printf("Error\nImpossible game.\n"), 0);
	return (1);
}

static int	map_valid_io(char **map)
{
	int	p;
	int	e;
	int	i;
	int	j;

	if (map == NULL)
		return (0);
	p = 0;
	e = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map_valid_char(map[i][j], &p, &e) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (p != 1 || e != 1)
		return (ft_printf("Error\nInvalid map: start/exit.\n"), 0);
	return (1);
}

int	map_is_valid(char **map, int *len_line, int *nb_line)
{
	size_t	len;
	int		i;

	if (map == NULL || *map == NULL)
		return (0);
	if (line_is_wall(map[0]) == 0)
		return (ft_printf("Error\nInvalid map\n"), 0);
	i = 0;
	len = ft_strlen(map[0]);
	if (len <= 2)
		return (ft_printf("Error\nInvalid map\n"), 0);
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) != len)
			return (ft_printf("Error\nInvalid map.\n"), 0);
		if (map[i + 1] != NULL && line_is_intermediate(map[i]) == 0)
			return (ft_printf("Error\nInvalid map.\n"), 0);
		i++;
	}
	if (line_is_wall(map[i - 1]) == 0)
		return (ft_printf("Error\nInvalid map.\n"), 0);
	*len_line = len;
	*nb_line = i;
	return (map_valid_io(map) && map_valid_game(map));
}
