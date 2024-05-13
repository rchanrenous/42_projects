CC			= cc
CFLAGS		= -Wall -Werror -Wextra

NAME		= push_swap
CHECKER		= checker

SRC_PS		= main.c
SRC_CHECKER	= main_checker.c checker.c
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

OBJS		= $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
OBJS_PS		= $(addprefix $(DIR_OBJ), $(SRC_PS:.c=.o))
OBJS_CHECKER = $(addprefix $(DIR_OBJ), $(SRC_CHECKER:.c=.o))

DIR_LIBFT	= ../lib/libft/
DIR_INCLUDE	= ${DIR_LIBFT}include
DIR_INCLUDE2= include/
LIBFT		= $(DIR_LIBFT)libft.a

all:		${NAME}

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c $(DIR_INCLUDE2)push_swap.h 
				${CC} ${CFLAGS} -I${DIR_INCLUDE} -I${DIR_INCLUDE2} -c $< -o $@

${LIBFT}:	
			make -C ${DIR_LIBFT}

${NAME}:	${LIBFT} ${OBJS} ${OBJS_PS} ${CHECKER}
			${CC} ${CFLAGS} ${OBJS} ${OBJS_PS} -o ${NAME} -I${DIR_INCLUDE} -L${DIR_LIBFT} -lft 

${CHECKER}:	${OBJS_CHECKER} 
			${CC} ${CFLAGS} ${OBJS} ${OBJS_CHECKER} -o ${CHECKER} -I${DIR_INCLUDE} -L${DIR_LIBFT} -lft 

clean:
			make -C ${DIR_LIBFT} clean
			rm -f ${OBJS} ${OBJS_PS} ${OBJS_CHECKER}

fclean:		clean
			rm -rf ${DIR_LIBFT}libft.a 
			rm -rf ${NAME}
			rm -rf ${CHECKER}

re:			fclean all

.PHONY:		all fclean clean re bonus
