# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 14:35:13 by yejlee2           #+#    #+#              #
#    Updated: 2023/08/10 09:33:57 by yejlee2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c \
		srcs/start_shell.c \
		srcs/init.c
OBJS = $(SRCS:.c=.o)
INCS = incs
LIBFT = libft

.c.o :
	$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCS)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lreadline \
    -L${HOME}/.brew/opt/readline/lib \
    -I${HOME}/.brew/opt/readline/include \
    -o $@

clean :
	make fclean -C $(LIBFT)
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re .c.o