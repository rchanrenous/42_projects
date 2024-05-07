cc				= gcc
CFLAGS			= -Wall -Werror -Wextra
LIB				= -lX11 -lXext

NAME			= so_long

DIR_MLX			= ./minilibx-linux/
DIR_INC_MLX		= $(DIR_MLX)

DIR_LIBFT		= libft/
DIR_INC_LIBFT	= $(DIR_LIBFT)include/

DIR_OBJ			= bin/
DIR_INC_SL		= include/
DIR_SRC			= src/

LIBFT			= $(DIR_LIBFT)libft.a
MLX				= $(DIR_MLX)libmlx.a

SRC				= main.c \
				  input.c \
				  map.c map2.c \
				  map_check.c map_check2.c \
				  t_mlx.c t_mlx_free.c \
				  img_init.c \
				  map_to_window.c map_inside_window.c \
				  map_move.c \
				  events.c


OBJ				= $(addprefix $(DIR_OBJ), $(SRC:.c=.o))

all:			$(NAME)

$(LIBFT):
				make -C $(DIR_LIBFT)

$(MLX):
				make -C $(DIR_MLX)

$(DIR_OBJ):
				mkdir $@

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c $(DIR_INC_SL)so_long.h #$(DIR_OBJ)
				$(cc) $(CFLAGS) -I$(DIR_INC_SL) -I$(DIR_INC_LIBFT) -I$(DIR_INC_MLX) -c $< -o $@

$(NAME):		$(LIBFT) $(MLX) $(DIR_OBJ) $(OBJ)
				$(cc) $(CFLAGS) $(OBJ) -o $(NAME) -I$(DIR_INC_SL) -I$(DIR_INC_LIBFT) -I$(DIR_INC_MLX) -L$(DIR_LIBFT) -lft -L$(DIR_MLX) -lmlx $(LIB)

clean:
				make -C $(DIR_LIBFT) clean
				make -C $(DIR_MLX) clean
				rm -rf $(DIR_OBJ)

fclean:			clean
				make -C $(DIR_LIBFT) fclean
				rm -f $(NAME)

re:				fclean	all

.PHONY:			all fclean clean re
