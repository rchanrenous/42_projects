/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:46:20 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 17:04:25 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	ft_printf("mouse: %d, %d %d\n", button, x, y);
	ft_printf("hide: %d\n", mlx_set_font(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->win_ptr, "hello"));
	return (0);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (0);
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 500, 500, "mouse");
	if (mlx->win_ptr == NULL)
		return (0);
	mlx_mouse_hook(mlx->win_ptr, &mouse_hook, mlx);
	mlx_loop(mlx->mlx_ptr);
}
