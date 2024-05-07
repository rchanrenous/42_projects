/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:56:30 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 16:06:34 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	wall_to_window(t_mlx *mlx, int i, int up)
{
	void	*img_cl;
	void	*img_cr;
	void	*img_wall;
	int		x;
	int		w;

	img_cl = mlx->img_c0;
	img_cr = mlx->img_c1;
	img_wall = mlx->img_wu;
	if (up != 1)
	{
		img_cl = mlx->img_c3;
		img_cr = mlx->img_c2;
		img_wall = mlx->img_wd;
	}
	i *= mlx->bg_h;
	w = mlx->bg_w;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_cl, 0, i);
	x = 1;
	while (x < mlx->len_line - 1)
	{
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_wall, x * w, i);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_cr, x * w, i);
}

static void	side_to_window(t_mlx *mlx, int i, int j, int left)
{
	void	*img_s;
	int		x;
	int		y;

	if (mlx == NULL)
		return ;
	img_s = mlx->img_wl;
	if (left != 1)
		img_s = mlx->img_wr;
	x = j * mlx->bg_w;
	y = i * mlx->bg_h;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img_s, x, y);
}

static int	window_move(t_mlx *mlx)
{
	int		x;
	int		y;
	char	*nb;

	nb = ft_itoa(mlx->nb_move);
	if (nb == NULL)
		return (ft_printf("Error\n"), 0);
	x = mlx->bg_w / 2;
	y = mlx->bg_h / 2;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR, nb);
	free(nb);
	return (1);
}

int	map_to_window(t_mlx *mlx, char **map, int keycode)
{
	int		i;
	int		j;

	if (map == NULL || *map == NULL || *(map + 1) == NULL || mlx == NULL)
		return (0);
	wall_to_window(mlx, 0, 1);
	i = 1;
	while (map[i + 1] != NULL)
	{
		if (map[i][0] == '\0' || map[i][1] == '\0')
			return (0);
		side_to_window(mlx, i, 0, 1);
		j = 1;
		while (map[i][j + 1] != '\0')
		{
			inside_to_window(mlx, keycode, i, j);
			j++;
		}
		side_to_window(mlx, i, j, 0);
		i++;
	}
	wall_to_window(mlx, i, 0);
	return (window_move(mlx));
}
