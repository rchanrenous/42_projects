/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:37:26 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 16:10:47 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_put_exit(char **map, t_mlx *mlx)
{
	if (map[mlx->e_i][mlx->e_j] != 'P' && map[mlx->e_i][mlx->e_j] != 'E')
		map[mlx->e_i][mlx->e_j] = 'E';
}

int	map_move(t_mlx *mlx, int down, int right)
{
	int		i;
	int		j;
	int		c_x;
	int		c_y;
	char	**map;

	map = mlx->map;
	map_find(map, 'P', &i, &j);
	if (map[i + down][j + right] == '1')
		return (0);
	mlx->nb_move += 1;
	if (map[i + down][j + right] == 'E')
	{
		map_find(map, 'C', &c_x, &c_y);
		if (c_x == -1 && c_y == -1)
			return (1);
	}
	map[i + down][j + right] = 'P';
	map[i][j] = '0';
	map_put_exit(map, mlx);
	return (-1);
}
