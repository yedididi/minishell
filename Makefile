# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 14:35:13 by yejlee2           #+#    #+#              #
#    Updated: 2023/08/29 16:09:18 by yejlee2          ###   ########.fr        #
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
		srcs/free_input.c \
		srcs/execute/execute_rdr_in.c \
		srcs/execute/execute_rdr_out.c \
		srcs/execute/builtin_one.c \
		srcs/execute/builtin_two.c \
		srcs/execute/builtin_three.c \
		srcs/execute/builtin_four.c \
		srcs/execute/execute_cmd.c \
		srcs/execute/execute_utils_one.c \
		srcs/execute/execute_utils_two.c \
		srcs/execute/execute_utils_three.c \
		srcs/execute/execute.c \
		srcs/execute/execute_pipe.c \
		srcs/execute/execute_error.c \
		srcs/parse/parse.c \
		srcs/parse/parser.c \
		srcs/parse/addlist.c \
		srcs/parse/expansion.c \
		srcs/parse/expansion_utils.c \
		srcs/parse/heredoc.c \
		srcs/parse/heredoc_utils.c \
		srcs/parse/utils.c \
		srcs/parse/utils2.c \
		srcs/parse/exit_status.c \
		srcs/parse/quote.c \
		srcs/parse/dollar_before_closed_quote.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c \
		get_next_line/ft_printf_utils_hex.c \
		get_next_line/ft_printf_utils.c \
		get_next_line/ft_printf.c
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
