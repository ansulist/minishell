# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 17:17:27 by ansulist          #+#    #+#              #
#    Updated: 2023/06/23 23:38:56 by ansulist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = \
	ft_atoi.c \
    ft_calloc.c \
	ft_bzero.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_itoa.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memset.c \
    ft_putchar_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_putstr_fd.c \
    ft_split.c \
    ft_strchr.c \
    ft_strdup.c \
    ft_striteri.c \
    ft_strjoin.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strlen.c \
    ft_strmapi.c \
    ft_strncmp.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_strtrim.c \
    ft_substr.c \
    ft_tolower.c \
    ft_toupper.c \
    ft_lstadd_back.c \
    ft_lstadd_front.c \
    ft_lstclear.c \
    ft_lstdelone.c \
    ft_lstiter.c \
    ft_lstlast.c \
    ft_lstmap.c \
    ft_lstnew.c \
    ft_lstsize.c \
    ft_strdup_2d.c \
    ft_strlen_2d.c \
    ft_2d_arr_to_list.c \
    ft_strjoin_3.c \
    ft_lst_remove_if.c \
    ft_lstfind.c \
    ft_strndup.c \
    ft_strreplace.c \
    ft_strncpy.c \
    ft_strcmp.c \
    ft_list_to_array.c \

OBJ = $(SRC:.c=.o)

HEADERS = ./includes

all: $(NAME)

$(NAME):
	@echo "Compiling in Progress .."
	@gcc -Wall -Wextra -Werror -c $(SRC) -I $(HEADERS) && ar rc $(NAME) $(OBJ)
	@ar -s $(NAME) $(OBJ)
	@echo "Finished!"
clean: 
	@echo "Removing all .o's ..."
	@/bin/rm -f $(OBJ) $(BONUS_O)
	@echo "Finished!"

fclean:
	@echo "Removing lib ..."
	@/bin/rm -f $(NAME)
	@echo "Finished!"

re: fclean all

.PHONY: all clean fclean re
