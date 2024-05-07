NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -pthread

SRC		= main.c \
		  init.c input.c \
		  forks.c \
		  thread.c \
		  philo.c \
		  log.c time.c \
		  routine.c routine_eat.c \

OBJ		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_DIR	= bin/

INC		= philo.h
INC_DIR	= ./

SRC_DIR	= src/

all: 		$(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME):			$(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME)


clean:
	rm -rf $(OBJ_DIR)

fclean:			clean
	rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
