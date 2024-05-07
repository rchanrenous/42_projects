/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:40:54 by rchan--r          #+#    #+#             */
/*   Updated: 2023/07/21 16:01:53 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	t_img_free(t_img *img)
{
	if (img == NULL)
		return ;
	if (img->img_ptr != NULL)
	{
		mlx_destroy_image(img->mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
	}
}

static int	t_mlx_textures_init(t_mlx *mlx, char *files[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx->textures[i].img_ptr = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (t_img_init_file(mlx->mlx_ptr, &(mlx->textures[i]), files[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	t_mlx_init(t_mlx *mlx, char *files[4])
{
	if (mlx == NULL)
		return (0);
	mlx->frame.img_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (ft_printf_fd(2, "Error\n mlx_init()\n"), 0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (mlx->win_ptr == NULL)
		return (ft_printf_fd(2, "Error\n mlx_new_window()\n"),
			mlx_destroy_display(mlx->mlx_ptr), free(mlx->mlx_ptr), 0);
	if (t_mlx_textures_init(mlx, files) == 0)
		return (t_mlx_free(mlx), 0);
	if (t_img_init(mlx->mlx_ptr, &(mlx->frame), WIDTH, HEIGHT) == 0)
		return (t_mlx_free(mlx), 0);
	return (1);
}

void	t_mlx_free(t_mlx *mlx)
{
	int	i;

	if (mlx->mlx_ptr == NULL)
		return ;
	t_img_free(&(mlx->frame));
	i = 0;
	while (i < 4)
	{
		if (mlx->textures[i].img_ptr != NULL)
			t_img_free(&(mlx->textures[i]));
		i++;
	}
	if (mlx->win_ptr != NULL)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	mlx->mlx_ptr = NULL;
}
