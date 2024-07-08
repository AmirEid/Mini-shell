/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:50:04 by aeid              #+#    #+#             */
/*   Updated: 2024/07/08 22:29:19 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../Libft/libft.h"
# include "../Printft/ft_printf.h"
# include <readline/readline.h>
#include <readline/history.h>
# include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <termios.h>
#include <limits.h>
//#include <linux/limits.h>


# define PATH_MAX 4096

typedef struct	s_data
{
	t_list	*mini_env;
	t_list	*tokens;
	int		list_size;
	int		current;
	int		start;
	int		exit_code;
	char	*pwd;
	char	*old_pwd;
	char	*args; //needs to be freed, result of readline//
	char	**env;
}	t_data;

extern t_data	g_data;
extern int		g_exit_code;

void	printTokens(t_list *tokens);
void	ft_signals(void);
int		ft_pwd(t_data *data);
int		ft_cd(t_list *tokens, t_data *data);

# include "lexer.h"
# include "builtins.h"
# include "parsing.h"
# include "execution.h"

#endif