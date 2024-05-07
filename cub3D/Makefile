cc				= gcc
CFLAGS			= -Wall -Werror -Wextra -MMD
LIB				= -lX11 -lXext -lm

NAME			= cub3D

DIR_MLX			= ../lib/minilibx-linux/
DIR_INC_MLX		= $(DIR_MLX)

DIR_LIBFT		= ../lib/libft/
DIR_INC_LIBFT	= $(DIR_LIBFT)include

DIR_OBJ			= bin/
DIR_INC_C3D		= include/
DIR_SRC			= src/

LIBFT			= $(DIR_LIBFT)libft.a
MLX				= $(DIR_MLX)libmlx.a

SRC				= main.c \
				  game.c display_frame.c t_img.c t_mlx.c hooks.c img_fill.c raycast.c movement.c t_player.c raycast_init.c raycast_dda.c display_minimap.c \
				  check_argv.c clean_map.c fill_color_param.c free_parse.c parse_param.c transition.c check_map.c\
				  copy_file.c fill_texture_param.c parse_map.c parsing.c\

OBJ				= $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
DPD				= $(OBJ:.o=.d)

all:			$(NAME)

$(LIBFT):
				make -C $(DIR_LIBFT)

$(MLX):
				make -C $(DIR_MLX)

$(DIR_OBJ):
				mkdir $@

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c
				$(cc) $(CFLAGS) -I$(DIR_INC_C3D) -I$(DIR_INC_LIBFT) -I$(DIR_INC_MLX) -c $< -o $@

-include $(DPD)

$(NAME):		$(LIBFT) $(MLX) $(DIR_OBJ) $(OBJ)
				$(cc) $(CFLAGS) $(OBJ) -o $(NAME) -I$(DIR_INC_C3D) -I$(DIR_INC_LIBFT) -I$(DIR_INC_MLX) -L$(DIR_LIBFT) -lft -L$(DIR_MLX) -lmlx $(LIB)

clean:
				make -C $(DIR_LIBFT) clean
				make -C $(DIR_MLX) clean
				rm -rf $(DIR_OBJ)

fclean:			clean
				make -C $(DIR_LIBFT) fclean
				rm -f $(NAME)

re:				fclean	all

.PHONY:			all fclean clean re
