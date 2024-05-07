/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_inside_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:56:30 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 16:00:51 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_center_obj(t_mlx *m, char c, int *x, int *y)
{
	if (c == 'C')
	{
		(*x) += (m->bg_w / 2) - (m->c_h / 2);
		(*y) += (m->bg_h / 2) - (m->c_w / 2);
	}
}

static void	map_center_perso(t_mlx *m, char c, int *x, int *y)
{
	if (c == 'w')
	{
		(*x) += (m->bg_w / 2) - (m->pu_w / 2);
		(*y) += (m->bg_h / 2) - (m->pu_h / 2);
	}
	else if (c == 'a')
	{
		(*x) += (m->bg_w / 2) - (m->pl_w / 2);
		(*y) += (m->bg_h / 2) - (m->pl_h / 2);
	}
	else if (c == 's')
	{
		(*x) += (m->bg_w / 2) - (m->pd_w / 2);
		(*y) += (m->bg_h / 2) - (m->pd_h / 2);
	}
	else if (c == 'd')
	{
		(*x) += (m->bg_w / 2) - (m->pr_w / 2);
		(*y) += (m->bg_h / 2) - (m->pr_h / 2);
	}
}

static void	perso_to_window(t_mlx *m, int keycode, int x, int y)
{
	void	*img_ptr;

	if ((char)keycode == 'w')
		img_ptr = m->img_pu;
	else if ((char)keycode == 'a')
		img_ptr = m->img_pl;
	else if ((char)keycode == 's')
		img_ptr = m->img_pd;
	else if ((char)keycode == 'd')
		img_ptr = m->img_pr;
	else
		return ;
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, img_ptr, x, y);
}

void	img_on_top(t_mlx *m, int kc, int i, int j)
{
	int	x;
	int	y;

	if (m == NULL)
		return ;
	x = j * m->bg_w;
	y = i * m->bg_h;
	if (m->map[i][j] == 'P')
	{
		map_center_perso(m, kc, &x, &y);
		perso_to_window(m, kc, x, y);
	}
	else if (m->map[i][j] == 'C')
	{
		map_center_obj(m, m->map[i][j], &x, &y);
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_obj, x, y);
	}
}

void	inside_to_window(t_mlx *m, int kc, int i, int j)
{
	int		x;
	int		y;

	if (m == NULL)
		return ;
	x = j * m->bg_w;
	y = i * m->bg_h;
	if (m->map[i][j] == '1')
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_obs, x, y);
	else if (i == m->e_i && j == m->e_j)
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_e, x, y);
	else
		mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_grd, x, y);
	img_on_top(m, kc, i, j);
}
