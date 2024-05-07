/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:08:33 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 16:26:53 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	img_init_bg(t_mlx *m, void **img_ptr, char *fn)
{
	int	w;
	int	h;

	w = -1;
	h = -1;
	if (m == NULL)
		return (0);
	if (m->bg_w == -1 && m->bg_h == -1)
		*img_ptr = mlx_xpm_file_to_image(m->mlx_ptr, fn, &m->bg_w, &m->bg_h);
	else
	{
		*img_ptr = mlx_xpm_file_to_image(m->mlx_ptr, fn, &w, &h);
		if (w != -1 && h != -1 && (w != m->bg_w || h != m->bg_h))
			return (ft_printf("Error\nInvalid image dimensions: %s\n", fn), 0);
	}
	if (*img_ptr == NULL)
		return (ft_printf("Error\nInvalid image %s.\n", fn), 0);
	return (1);
}

int	img_init_all_bg(t_mlx *mlx)
{
	if (img_init_bg(mlx, &(mlx->img_wu), IMG_WU) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_wd), IMG_WD) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_wl), IMG_WL) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_wr), IMG_WR) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_c0), IMG_C0) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_c1), IMG_C1) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_c2), IMG_C2) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_c3), IMG_C3) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_e), IMG_E) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_grd), IMG_GROUND) == 0)
		return (0);
	if (img_init_bg(mlx, &(mlx->img_obs), IMG_OBS) == 0)
		return (0);
	return (1);
}

int	img_init_perso(t_mlx *m)
{
	if (m == NULL)
		return (0);
	m->img_pu = mlx_xpm_file_to_image(m->mlx_ptr, IMG_PU, &m->pu_w, &m->pu_h);
	if (m->img_pu == NULL)
		return (ft_printf("Error\nInvalid character image %s.\n", IMG_PU), 0);
	m->img_pd = mlx_xpm_file_to_image(m->mlx_ptr, IMG_PD, &m->pd_w, &m->pd_h);
	if (m->img_pd == NULL)
		return (ft_printf("Error\nInvalid character image %s.\n", IMG_PD), 0);
	m->img_pl = mlx_xpm_file_to_image(m->mlx_ptr, IMG_PL, &m->pl_w, &m->pl_h);
	if (m->img_pl == NULL)
		return (ft_printf("Error\nInvalid character image %s.\n", IMG_PL), 0);
	m->img_pr = mlx_xpm_file_to_image(m->mlx_ptr, IMG_PR, &m->pr_w, &m->pr_h);
	if (m->img_pr == NULL)
		return (ft_printf("Error\nInvalid character image %s.\n", IMG_PR), 0);
	return (1);
}

int	img_init_obj(t_mlx *m)
{
	if (m == NULL)
		return (0);
	m->img_obj = mlx_xpm_file_to_image(m->mlx_ptr, IMG_C, &m->c_w, &m->c_h);
	if (m->img_obj == NULL)
		return (ft_printf("Error\nInvalid object image.\n"), 0);
	return (1);
}

int	img_valid_dimensions(t_mlx *mlx)
{
	if (mlx->pu_w > mlx->bg_w || mlx->pu_h > mlx->bg_h)
		return (ft_printf("Error\nInvalid character image dimensions"), 0);
	if (mlx->pd_w > mlx->bg_w || mlx->pd_h > mlx->bg_h)
		return (ft_printf("Error\nInvalid character image dimensions"), 0);
	if (mlx->pl_w > mlx->bg_w || mlx->pl_h > mlx->bg_h)
		return (ft_printf("Error\nInvalid character image dimensions"), 0);
	if (mlx->pr_w > mlx->bg_w || mlx->pr_h > mlx->bg_h)
		return (ft_printf("Error\nInvalid character image dimensions"), 0);
	if (mlx->c_w > mlx->bg_w || mlx->c_h > mlx->bg_h)
		return (ft_printf("Error\nInvalid object image dimensions"), 0);
	return (1);
}
