/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:17:15 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 14:25:10 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	t_mlx_fill_int(t_mlx *mlx, int len_line, int nb_line)
{
	mlx->len_line = len_line;
	mlx->nb_line = nb_line;
	mlx->nb_move = 0;
	mlx->e_i = -1;
	mlx->e_j = -1;
	mlx->bg_w = -1;
	mlx->bg_h = -1;
	mlx->pu_w = -1;
	mlx->pu_h = -1;
	mlx->pd_w = -1;
	mlx->pd_h = -1;
	mlx->pl_w = -1;
	mlx->pl_h = -1;
	mlx->pr_w = -1;
	mlx->pr_h = -1;
	mlx->c_w = -1;
	mlx->c_h = -1;
}

static void	t_mlx_fill_ptr(t_mlx *mlx, char **map)
{
	mlx->map = map;
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_wu = NULL;
	mlx->img_wd = NULL;
	mlx->img_wl = NULL;
	mlx->img_wr = NULL;
	mlx->img_c0 = NULL;
	mlx->img_c1 = NULL;
	mlx->img_c2 = NULL;
	mlx->img_c3 = NULL;
	mlx->img_pu = NULL;
	mlx->img_pd = NULL;
	mlx->img_pl = NULL;
	mlx->img_pr = NULL;
	mlx->img_e = NULL;
	mlx->img_obj = NULL;
	mlx->img_grd = NULL;
	mlx->img_obs = NULL;
}

t_mlx	*t_mlx_init(char **map, int len_line, int nb_line)
{
	t_mlx	*mlx;
	int		size_x;
	int		size_y;

	if (map == NULL || len_line <= 0 || nb_line <= 0)
		return (NULL);
	mlx = malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (map_free(&map), NULL);
	t_mlx_fill_int(mlx, len_line, nb_line);
	t_mlx_fill_ptr(mlx, map);
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (t_mlx_free(&mlx), NULL);
	if (!img_init_all_bg(mlx) || !img_init_perso(mlx) || !img_init_obj(mlx))
		return (t_mlx_free(&mlx), NULL);
	if (!img_valid_dimensions(mlx))
		return (t_mlx_free(&mlx), NULL);
	size_x = mlx->bg_w * len_line;
	size_y = mlx->bg_h * nb_line;
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, size_x, size_y, WIN_NAME);
	if (mlx->win_ptr == NULL)
		return (t_mlx_free(&mlx), NULL);
	return (mlx);
}
