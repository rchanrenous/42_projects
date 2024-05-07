/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:22:58 by rchan--r          #+#    #+#             */
/*   Updated: 2023/07/21 15:32:29 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_get_texture(t_game *game, t_raycast *raycast)
{
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x < 0)
			raycast->texture = &(game->mlx.textures[NO]);
		else
			raycast->texture = &(game->mlx.textures[SO]);
	}
	else
	{
		if (raycast->ray_dir_y < 0)
			raycast->texture = &(game->mlx.textures[WE]);
		else
			raycast->texture = &(game->mlx.textures[EA]);
	}
}

static void	raycast_compute_texture(t_game *g, t_raycast *rc, double d, int lh)
{
	if (rc->side == 0)
		rc->wall_x = g->player.pos_y + d * rc->ray_dir_y;
	else
		rc->wall_x = g->player.pos_x + d * rc->ray_dir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = rc->wall_x * (double)rc->texture->w;
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = rc->texture->w - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = rc->texture->w - rc->tex_x - 1;
	rc->step = 1.0 * rc->texture->h / lh;
	rc->tex_pos = (rc->draw_start - HEIGHT / 2 + lh / 2) * rc->step;
}

static void	raycast_compute(int x, t_game *game, t_raycast *rc)
{
	double		perp_wall_dist;
	int			line_height;

	raycast_init(rc, game, x);
	raycast_dda(rc, game);
	if (rc->side == 0)
		perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	line_height = HEIGHT / perp_wall_dist;
	rc->draw_start = -line_height / 2 + HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = line_height / 2 + HEIGHT / 2;
	if (rc->draw_end >= HEIGHT)
		rc->draw_end = HEIGHT - 1;
	raycast_get_texture(game, rc);
	raycast_compute_texture(game, rc, perp_wall_dist, line_height);
}

void	raycast(t_game *game)
{
	int			x;
	int			y;
	t_raycast	raycast;

	game_update_moves(game);
	x = 0;
	while (x < WIDTH)
	{
		raycast_compute(x, game, &raycast);
		y = 0;
		while (y < HEIGHT)
		{
			if (raycast.draw_start <= y && y <= raycast.draw_end)
				raycast_fill_img(game, x, y, &raycast);
			else
				img_fill_ceiling_floor(game, x, y);
			y++;
		}
		x++;
	}
}
