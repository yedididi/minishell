# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 14:35:13 by yejlee2           #+#    #+#              #
#    Updated: 2023/08/12 11:23:24 by yejlee2          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/main.c \
		srcs/main_utils.c \
		srcs/start_shell.c \
		srcs/init.c \
		srcs/env_list.c \
		srcs/env.c \
		srcs/execute/execute.c \
		srcs/parse/parse.c \
		srcs/parse/parse_list.c \
		srcs/parse/parse_util.c
OBJS = $(SRCS:.c=.o)
INCS = incs
LIBFT = libft/libft.a

.c.o :
	$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCS)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline \
    -L${HOME}/.brew/opt/readline/lib \
    -I${HOME}/.brew/opt/readline/include \
    -o $@

$(LIBFT) : 
	make -C $(dir $(LIBFT))

clean :
	make -C $(dir $(LIBFT)) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(dir $(LIBFT)) fclean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re .c.o