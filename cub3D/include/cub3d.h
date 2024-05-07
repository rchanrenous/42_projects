/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:50:19 by rchan--r          #+#    #+#             */
/*   Updated: 2023/07/21 15:35:31 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>
# include "libft.h"
# include "cub3d_struct.h"

// PARSING
int			parsing(t_game *game, t_parse *prs, int ac, char **av);
int			check_argv(int ac, char **av);
int			copy_file(t_parse *prs, char *file, int ret);
int			parse_param(t_parse *prs, int i, char *tex);
int			parse_map(t_parse *prs);
int			fill_color_param(t_parse *prs, char *tp);
int			fill_texture_param(t_parse *prs, char *tex, char *tp);
int			check_map(t_parse *prs);
int			clean_map_line(t_parse *prs);
void		free_parse(t_parse *prs);
int			transition(t_game *game, t_parse *prs);

// GAME.C 
int			game_init(t_game *game);
void		game_free(t_game game);

// IMG_FILL_DISPLAY.C
void		img_fill_pixel(t_img img, int x, int y, unsigned int color);
void		img_fill_ceiling_floor(t_game *game, int x, int y);
void		raycast_fill_img(t_game *game, int x, int y, t_raycast *raycast);

// MOVEMENT.C
void		game_update_moves(t_game *game);

// RAYCAST.C
void		raycast(t_game *game);

// RAYCAST_INIT.C
void		raycast_init(t_raycast *raycast, t_game *game, int x);

// RAYCAST_DDA.C
void		raycast_dda(t_raycast *raycast, t_game *game);

// DISPLAY_FRAME.C
int			display_frame(void *param);

// DISPLAY_MINIMAP.C
int			display_minimap(t_game *game);

//T_IMG.C
int			t_img_init(void *mlx_ptr, t_img *img, int width, int height);
int			t_img_init_file(void *mlx_ptr, t_img *img, char *file);

// T_MLX.C
int			t_mlx_is_valid(t_mlx *mlx);
int			t_mlx_init(t_mlx *mlx, char *files[4]);
void		t_mlx_free(t_mlx *mlx);

// HOOKS.C
int			key_up_hook(int keycode, void *param);
int			key_down_hook(int keycode, void *param);
int			close_window(void *param);

// T_PLAYER.C
t_player	player_init(char **map);

#endif
