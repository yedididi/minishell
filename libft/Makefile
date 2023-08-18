# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:50:11 by yejlee2           #+#    #+#              #
#    Updated: 2022/12/12 17:23:48 by yejlee2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cc = cc
NAME = libft.a
CFLAGS = -c -Wall -Wextra -Werror
SRCS = *.c
BON_O = ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o ft_lstdelone.o ft_lstiter.o ft_lstlast.o ft_lstmap.o ft_lstnew.o ft_lstsize.o
MAN_O = ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_strchr.o ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o ft_strtrim.o ft_strrchr.o ft_substr.o ft_tolower.o ft_bzero.o ft_atoi.o ft_calloc.o ft_strdup.o ft_split.o ft_itoa.o ft_toupper.o
INCS = .

ifdef IS_BONUS
	OBJ_F = $(BON_O) $(MAN_O)
else
	OBJ_F = $(MAN_O)
endif

all : $(NAME)

$(NAME) : $(OBJ_F)
	ar rscv  $(NAME) $(OBJ_F)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCS)

bonus :
	make IS_BONUS=1 all

clean :
	rm -f $(BON_O) $(MAN_O)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re .c.o
