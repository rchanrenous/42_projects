/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:57:24 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 14:14:40 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_mlx	*mlx;

	mlx = t_mlx_init(NULL, 10, 20);
	(void) mlx;
	if (mlx == NULL)
		return (0);
	//mlx_loop(mlx->mlx_ptr);
	//t_mlx_free(&mlx);
}
