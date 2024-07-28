/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:59 by anoukmourna       #+#    #+#             */
/*   Updated: 2024/07/28 17:48:26 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./headers/minishell.h"

/** Signal handler for the SIGINT signal (ctrl+c) */
void	sigint_handler(int sig)
{
	(void)sig;
	g_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//anouk, possiamo usare solo un globale per l'exit code 
/** Signal handler for the SIGINT signal inside a heredoc (ctrl+c) */
/*
void	ft_heredoc_handler(int sig)
{
	(void)sig;
	printf("\n");
	g_status = 130;
	exit(g_status);
}
*/

void	ft_sig_term(t_data *data)
{
	//ft_clear_history(data);
	write(STDOUT_FILENO, "exit\n", 5);
	free_all(data);
	exit(0);
}

/** Uses signal function associate to handlers */
void	ft_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}