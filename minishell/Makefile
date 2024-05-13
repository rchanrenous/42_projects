NAME		= minishell
CC			= gcc
CFLAGS 		= -Wall -Wextra -Werror -g3
LFLAGS		= -lreadline

LIBFT		= libft.a
DIR_LIBFT	= ../lib/libft/

DIR_SRC 	= src/
DIR_OBJ		= bin/
DIR_INC		= include/
DIR_INC_LIBFT	= $(DIR_LIBFT)include/

SRC			= main.c \
			  env_utils.c env_export.c env_unset.c ft_getenv.c ft_env.c\
			  index_end_token.c quotes.c check_char.c lst_add_strldup.c \
			  str_expand_nq.c expand.c str_protect.c \
			  line_to_cmds.c \
			  parse_cmd.c t_redir.c \
			  cmd_resolve_quotes.c str_get_token.c token_sq.c token_dq.c token_nq.c \
			  parse.c cmd.c \
			  line_exec.c get_line.c line_check.c pipe_update_fds.c redir_update_fds.c redir_in2_update_fds.c error.c cmd_system.c signal.c \
			  ft_exit.c ft_cd.c ft_echo.c ft_pwd.c get_cwd_val.c
			  

OBJ			= $(addprefix $(DIR_OBJ), $(SRC:.c=.o))

all:			$(NAME)			

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c
	$(CC) $(CFLAGS) -I$(DIR_INC) -I$(DIR_INC_LIBFT) -c $< -o $@ $(LFLAGS)

$(DIR_LIBFT)$(LIBFT):
	${MAKE} -C $(DIR_LIBFT)

$(NAME):		$(DIR_OBJ) $(DIR_LIBFT)$(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -I$(DIR_INC) -I$(DIR_INC_LIBFT) $(OBJ) -o $(NAME) $(LFLAGS) -L$(DIR_LIBFT) -lft

$(DIR_OBJ):
	mkdir $@

clean:
	make -C $(DIR_LIBFT) clean
	rm -rf $(DIR_OBJ)

fclean:			clean
	make -C $(DIR_LIBFT) fclean
	rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
