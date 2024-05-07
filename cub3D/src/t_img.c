/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:47:50 by rchan--r          #+#    #+#             */
/*   Updated: 2023/07/21 16:04:18 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	t_img_init(void *mlx_ptr, t_img *img, int width, int height)
{
	if (img == NULL)
		return (0);
	img->mlx_ptr = mlx_ptr;
	img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->img_ptr == NULL)
		return (ft_printf_fd(2, "Error\n mlx_new_image()\n"), 0);
	img->buf = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->size_line), &(img->endian));
	if (img->buf == NULL)
	{
		ft_printf_fd(2, "Error\n mlx_get_data_addr()\n");
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		return (0);
	}
	img->bpp /= 8;
	return (1);
}

int	t_img_init_file(void *mlx_ptr, t_img *img, char *file)
{
	if (img == NULL)
		return (0);
	img->mlx_ptr = mlx_ptr;
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file, &(img->w), &(img->h));
	if (img->img_ptr == NULL)
		return (ft_printf_fd(2, "Error\n mlx_xpm_file_to_image()\n"), 0);
	img->buf = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->size_line), &(img->endian));
	if (img->buf == NULL)
		return (ft_printf_fd(2, "Error\n mlx_get_data_addr()\n"),
			mlx_destroy_image(mlx_ptr, img->img_ptr),
			img->img_ptr = NULL, 0);
	img->bpp /= 8;
	return (1);
}
