CC			= cc
CFLAGS		= -Wall -Werror -Wextra

NAME		= push_swap
BONUS		= checker

SRC_PS		= main.c
SRC_BONUS	= main_checker.c checker.c
SRC			= input.c \
			  instr.c instr2.c instr_print2.c instr_print.c \
			  stack.c stack2.c stack3.c \
			  stack_instr.c stack_instr2.c \
			  node.c node2.c \
			  solve.c \
			  solve3_1.c solve3_2.c \
			  solve5.c

DIR_OBJ		= bin/
DIR_SRC		= src/
DIR_BONUS	= bonus/
DIR_OBJ_BONUS	= bonus/bin/

OBJS		= $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
OBJS_PS		= $(addprefix $(DIR_OBJ), $(SRC_PS:.c=.o))
OBJS_BONUS = $(addprefix $(DIR_OBJ_BONUS), $(SRC_BONUS:.c=.o))

DIR_LIBFT	= ../lib/libft/
DIR_INCLUDE	= ${DIR_LIBFT}include
DIR_INCLUDE2= include/
LIBFT		= $(DIR_LIBFT)libft.a

all:		${NAME}

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c $(DIR_INCLUDE2)push_swap.h 
				${CC} ${CFLAGS} -I${DIR_INCLUDE} -I${DIR_INCLUDE2} -c $< -o $@

$(DIR_OBJ_BONUS)%.o:	$(DIR_BONUS)%.c $(DIR_INCLUDE2)push_swap.h
						${CC} ${CFLAGS} -I${DIR_INCLUDE} -I${DIR_INCLUDE2} -c $< -o $@

${LIBFT}:	
			make -C ${DIR_LIBFT}

${NAME}:	${LIBFT} ${OBJS} ${OBJS_PS}
			${CC} ${CFLAGS} ${OBJS} ${OBJS_PS} -o ${NAME} -I${DIR_INCLUDE} -L${DIR_LIBFT} -lft 

${BONUS}:	${NAME} ${OBJS_BONUS} 
			${CC} ${CFLAGS} ${OBJS} ${OBJS_BONUS} -o ${BONUS} -I${DIR_INCLUDE} -L${DIR_LIBFT} -lft 

bonus:		${BONUS}

clean:
			make -C ${DIR_LIBFT} clean
			rm -f ${OBJS} ${OBJS_PS} ${OBJS_BONUS}

fclean:		clean
			rm -rf ${DIR_LIBFT}libft.a 
			rm -rf ${NAME}
			rm -rf ${BONUS}

re:			fclean all

.PHONY:		all fclean clean re bonus
