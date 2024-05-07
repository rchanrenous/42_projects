/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:22:54 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/13 14:35:51 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_parse	prs;
	t_game	game;

	prs = (t_parse){0};
	game = (t_game){0};
	if (parsing(&game, &prs, ac, av))
		return (game_free(game), 0);
	if (game_init(&game) == 0)
		return (0);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, &key_down_hook, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, &key_up_hook, &game);
	mlx_hook(game.mlx.win_ptr, 17, 0, &close_window, &(game.mlx));
	mlx_loop_hook(game.mlx.mlx_ptr, &display_frame, &game);
	mlx_loop(game.mlx.mlx_ptr);
	game_free(game);
	return (0);
}
