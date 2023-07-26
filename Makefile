# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 00:21:24 by ansulist          #+#    #+#              #
#    Updated: 2023/07/19 12:09:43 by ansulist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  cd.c \
		echo.c \
		env.c \
		main.c \
		pwd.c \
		exec_command_line.c \
		export.c \
		get_path.c \
		unset.c \
		pipeline_exec2.c \
		left_redirect.c \
		right_redirect.c \
		heredoc.c \
		initialize.c \
		ft_splitline.c \
		utils.c \
		set_spaces.c \
		check_errors.c \
		signal_config.c \
		utils3.c \
		exit.c \
		double_left_redirect.c \

OBJS = ${SRCS:.c=.o}
CHECK_OBJS = ${CHECK_SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${MAKE} -C libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -lreadline -o ${NAME}

clean: 
	@${MAKE} -C libft clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re