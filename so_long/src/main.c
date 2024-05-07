/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:01:55 by rchan--r          #+#    #+#             */
/*   Updated: 2024/05/07 19:45:56 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2 || filename_valid(argv[1]) == 0)
		return (0);
	if (init_so_long(&mlx, argv[1]) == 0)
		return (0);
	if (map_to_window(mlx, mlx->map, (int) 's') == 0)
		return (t_mlx_free(&mlx), 0);
	mlx_key_hook(mlx->win_ptr, &key_hook, (void *)mlx);
	mlx_hook(mlx->win_ptr, 17, 0, &close_window, (void *)mlx);
	mlx_loop_hook(mlx->mlx_ptr, &display_map, (void *)mlx);
	mlx_loop(mlx->mlx_ptr);
	t_mlx_free(&mlx);
}
