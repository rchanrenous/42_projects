/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mlx_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:02:07 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/13 12:10:27 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	t_mlx_print(t_mlx *mlx)
{
	ft_printf("print mlx\n");
	ft_printf("exit: %d %d\n", mlx->e_i, mlx->e_j);
	ft_printf("bg: %d %d\n", mlx->bg_w, mlx->bg_h);
	ft_printf("pu: %d %d\n", mlx->pu_w, mlx->pu_h);
	ft_printf("pd: %d %d\n", mlx->pd_w, mlx->pd_h);
	ft_printf("pl: %d %d\n", mlx->pl_w, mlx->pl_h);
	ft_printf("pr: %d %d\n", mlx->pr_w, mlx->pr_h);
	ft_printf("c: %d %d\n", mlx->c_w, mlx->c_h);
	ft_printf("line: %d %d\n", mlx->nb_line, mlx->len_line);
	ft_printf("nb_move: %d\n", mlx->nb_move);
}
