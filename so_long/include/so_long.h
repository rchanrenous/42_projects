/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:54:49 by rchan--r          #+#    #+#             */
/*   Updated: 2024/05/07 19:45:48 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <X11/keysym.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define MAP_INIT_SIZE 10

# define WIN_NAME "so_long"

# ifndef COLOR
#  define COLOR 65280
# endif

# ifndef IMG_WU
#  define IMG_WU "xpm/pokemon/wu_50.xpm"
# endif

# ifndef IMG_WD
#  define IMG_WD "xpm/pokemon/wd_50.xpm"
# endif

# ifndef IMG_WL
#  define IMG_WL "xpm/pokemon/wl_50.xpm"
# endif

# ifndef IMG_WR
#  define IMG_WR "xpm/pokemon/wr_50.xpm"
# endif

# ifndef IMG_C0
#  define IMG_C0 "xpm/pokemon/c0_50.xpm"
# endif

# ifndef IMG_C1
#  define IMG_C1 "xpm/pokemon/c1_50.xpm"
# endif

# ifndef IMG_C2
#  define IMG_C2 "xpm/pokemon/c2_50.xpm"
# endif

# ifndef IMG_C3
#  define IMG_C3 "xpm/pokemon/c3_50.xpm"
# endif

# ifndef IMG_E
#  define IMG_E "xpm/pokemon/e_50.xpm"
# endif

# ifndef IMG_PD
#  define IMG_PD "xpm/pokemon/p_20_30.xpm"
# endif

# ifndef IMG_PU
#  define IMG_PU "xpm/pokemon/pu_21_30.xpm"
# endif

# ifndef IMG_PL
#  define IMG_PL "xpm/pokemon/pl_22_30.xpm"
# endif

# ifndef IMG_PR
#  define IMG_PR "xpm/pokemon/pr_22_30.xpm"
# endif

# ifndef IMG_C
#  define IMG_C "xpm/pokemon/obj_16_15.xpm"
# endif

# ifndef IMG_GROUND
#  define IMG_GROUND "xpm/pokemon/ground_50.xpm"
# endif

# ifndef IMG_OBS
#  define IMG_OBS "xpm/pokemon/obstacle_50.xpm"
# endif

typedef struct s_mlx
{
	int		e_i;
	int		e_j;
	int		bg_w;
	int		bg_h;
	int		pu_w;
	int		pu_h;
	int		pd_w;
	int		pd_h;
	int		pl_w;
	int		pl_h;
	int		pr_w;
	int		pr_h;
	int		c_w;
	int		c_h;
	int		len_line;
	int		nb_line;
	int		nb_move;
	char	**map;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_wu;
	void	*img_wd;
	void	*img_wl;
	void	*img_wr;
	void	*img_c0;
	void	*img_c1;
	void	*img_c2;
	void	*img_c3;
	void	*img_pu;
	void	*img_pd;
	void	*img_pl;
	void	*img_pr;
	void	*img_e;
	void	*img_obj;
	void	*img_grd;
	void	*img_obs;
}				t_mlx;

int		key_hook(int keycode, void *param);
int		close_window(void *param);
int		display_map(void *param);

int		init_so_long(t_mlx **mlx, char *filename);
int		filename_valid(char *filename);

int		map_is_valid(char **map, int *len_line, int *nb_line);
int		map_append_line(char ***map, char *str);
void	map_free(char ***map);
char	**map_duplicate(char **map);
void	map_find(char **map, char c, int *i, int *j);
int		map_valid_char(char m, int *p, int *e);
int		map_move(t_mlx *mlx, int down, int right);

int		line_is_wall(char *line);
int		line_is_intermediate(char *line);

t_mlx	*t_mlx_init(char **map, int len_line, int nb_line);
void	t_mlx_free(t_mlx **mlx);

int		img_init_all_bg(t_mlx *mlx);
int		img_init_perso(t_mlx *mlx);
int		img_init_obj(t_mlx *mlx);
int		img_valid_dimensions(t_mlx *mlx);

void	inside_to_window(t_mlx *m, int kc, int i, int j);
int		map_to_window(t_mlx *mlx, char **map, int keycode);

#endif
