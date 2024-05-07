/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:23:39 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 17:20:44 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, void *param)
{
	int	res;

	res = 0;
	if (keycode == 'w')
		res = map_move((t_mlx *)param, -1, 0);
	else if (keycode == 'a')
		res = map_move((t_mlx *)param, 0, -1);
	else if (keycode == 's')
		res = map_move((t_mlx *)param, 1, 0);
	else if (keycode == 'd')
		res = map_move((t_mlx *)param, 0, 1);
	else if (keycode != ESC)
		return (0);
	if (res == 1 || keycode == ESC)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	mlx_clear_window(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->win_ptr);
	if (map_to_window((t_mlx *)param, ((t_mlx *)param)->map, keycode) == 0)
		return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
	return (1);
}

int	close_window(void *param)
{
	return (mlx_loop_end(((t_mlx *)param)->mlx_ptr));
}
