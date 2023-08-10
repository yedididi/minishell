/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee2 <yejlee2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 14:39:58 by yejlee2           #+#    #+#             */
/*   Updated: 2023/08/10 11:37:17 by yejlee2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

void	error();

void    rl_replace_line (const char *text, int clear_undo);

void    handler(int signum);
void	start_shell(void);

void    init(int argc, char *argv[], char *envp[]);

int	is_whitespace(char *line);

void	parse();

void	execute();

#endif