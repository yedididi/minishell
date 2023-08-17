# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 14:35:13 by yejlee2           #+#    #+#              #
#    Updated: 2023/08/17 11:36:31 by yejlee2          ###   ########.fr        #
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
		srcs/execute/execute_rdr.c \
		srcs/execute/builtin_one.c \
		srcs/execute/builtin_two.c \
		srcs/execute/execute_cmd.c \
		srcs/execute/execute_utils.c \
		srcs/execute/execute.c \
		srcs/parse/parse.c \
		srcs/parse/parser.c \
		srcs/parse/parse_list.c \
		srcs/parse/parse_utils.c \
		srcs/parse/parse_heredoc.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c
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

only : 
	make fclean
	make all
	make clean

.PHONY : all clean fclean re .c.o