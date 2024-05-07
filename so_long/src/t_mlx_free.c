/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:27:20 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 14:23:20 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	t_mlx_free_wall(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img_wu != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wu);
		mlx->img_wu = NULL;
	}
	if (mlx->img_wd != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wd);
		mlx->img_wd = NULL;
	}
	if (mlx->img_wl != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wl);
		mlx->img_wl = NULL;
	}
	if (mlx->img_wr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_wr);
		mlx->img_wr = NULL;
	}
}

static void	t_mlx_free_corner(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img_c0 != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_c0);
		mlx->img_c0 = NULL;
	}
	if (mlx->img_c1 != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_c1);
		mlx->img_c1 = NULL;
	}
	if (mlx->img_c2 != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_c2);
		mlx->img_c2 = NULL;
	}
	if (mlx->img_c3 != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_c3);
		mlx->img_c3 = NULL;
	}
}

static void	t_mlx_free_perso(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img_pu != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_pu);
		mlx->img_pu = NULL;
	}
	if (mlx->img_pd != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_pd);
		mlx->img_pd = NULL;
	}
	if (mlx->img_pl != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_pl);
		mlx->img_pl = NULL;
	}
	if (mlx->img_pr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_pr);
		mlx->img_pr = NULL;
	}
}

static void	t_mlx_free_other(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img_e != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_e);
		mlx->img_e = NULL;
	}
	if (mlx->img_obj != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_obj);
		mlx->img_obj = NULL;
	}
	if (mlx->img_grd != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_grd);
		mlx->img_grd = NULL;
	}
	if (mlx->img_obs != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_obs);
		mlx->img_obs = NULL;
	}
}

void	t_mlx_free(t_mlx **mlx)
{
	if (mlx == NULL)
		return ;
	if ((*mlx)->map != NULL)
		map_free(&((*mlx)->map));
	t_mlx_free_wall(*mlx);
	t_mlx_free_corner(*mlx);
	t_mlx_free_other(*mlx);
	t_mlx_free_perso(*mlx);
	if ((*mlx)->win_ptr != NULL)
		mlx_destroy_window((*mlx)->mlx_ptr, (*mlx)->win_ptr);
	if ((*mlx)->mlx_ptr != NULL)
	{
		mlx_destroy_display((*mlx)->mlx_ptr);
		free((*mlx)->mlx_ptr);
	}
	free(*mlx);
	*mlx = NULL;
}
