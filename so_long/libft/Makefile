# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 17:20:18 by rchan--r          #+#    #+#              #
#    Updated: 2023/01/13 18:29:17 by rchan--r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
cc			= gcc
CFLAGS		= -Wall -Werror -Wextra
AR			= ar -rc

NAME		= libft.a

DIR_OBJ		= bin/
DIR_INC		= include/
DIR_SRC		= src/
DIR_MAND	= mandatory/
DIR_BONUS	= bonus/
DIR_EXTRA	= extra/

PATH_INC	= -I$(DIR_INC)

OBJ_MAND	= $(addprefix $(DIR_OBJ), $(addprefix $(DIR_MAND), $(SRC_MAND:.c=.o)))
OBJ_BONUS	= $(addprefix $(DIR_OBJ), $(addprefix $(DIR_BONUS), $(SRC_BONUS:.c=.o)))
OBJ_EXTRA	= $(addprefix $(DIR_OBJ), $(addprefix $(DIR_EXTRA), $(SRC_EXTRA:.c=.o)))

SRC_MAND	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		  	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		  	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		  	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		  	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c \

SRC_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			  ft_lstiter.c ft_lstmap.c \

SRC_EXTRA	= get_next_line.c get_next_line_utils.c \
			  ft_printf.c len.c print.c format.c format2.c \
			  


#OBJS		= ${SRCS:.c=.o}

#OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all:		${NAME} 
	
#.c.o:		
#			gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

$(DIR_OBJ):
				mkdir $@

$(DIR_OBJ)%:
				mkdir $@

$(DIR_OBJ)%.o:	$(DIR_SRC)%.c
				$(cc) -c $(CFLAGS) $(PATH_INC) $< -o $@
			

${NAME}:	${DIR_OBJ} ${DIR_OBJ}${DIR_MAND} ${DIR_OBJ}${DIR_BONUS} ${DIR_OBJ}${DIR_EXTRA} ${OBJ_MAND} ${OBJ_BONUS} ${OBJ_EXTRA}
			${AR} ${NAME} ${OBJ_MAND} ${OBJ_BONUS} ${OBJ_EXTRA}
			ranlib ${NAME}

#bonus:		all ${OBJS_BONUS}
#			ar -r ${NAME} ${OBJS_BONUS}
#			ranlib ${NAME}
			
clean:
			rm -rf ${DIR_OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all fclean clean re
