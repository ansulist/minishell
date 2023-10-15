# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 00:21:24 by ansulist          #+#    #+#              #
#    Updated: 2023/10/13 21:20:45 by ansulist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  cd.c \
		cd_utils.c \
		echo.c \
		env.c \
		env_utils.c \
		env_check.c \
		main.c \
		pwd.c \
		exec_command_line.c \
		check_builtins.c \
		export.c \
		export_utils.c \
		get_path.c \
		get_path_free.c \
		get_path_utils.c \
		unset.c \
		pipeline_exec2.c \
		left_redirect.c \
		right_redirect.c \
		heredoc.c \
		initialize.c \
		ft_splitline.c \
		ft_splitline2.c \
		ft_splitline3.c \
		split_words.c \
		utils.c \
		set_spaces.c \
		set_redirecspace.c \
		check_errors.c \
		check_errors2.c \
		signal_config.c \
		utils2.c \
		utils3.c \
		exit.c \
		double_left_redirect.c \
		expand.c \
		expand_utils.c \
		expand_helper.c \
		free_struct.c \

OBJS = ${SRCS:.c=.o}
CHECK_OBJS = ${CHECK_SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

RM = rm -rf

all: ${NAME}
${NAME}: ${OBJS}
	@${MAKE} -C libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -lreadline -I/$(USER)/ansulist/.brew/opt/readline/include -L/Users/$(USER)/.brew/opt/readline/lib -o ${NAME}

clean: 
	@${MAKE} -C libft clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C libft fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re



