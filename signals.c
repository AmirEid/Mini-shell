/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:59 by anoukmourna       #+#    #+#             */
/*   Updated: 2024/08/06 19:11:12 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./headers/minishell.h"

/** Signal handler for the SIGINT signal (ctrl+c) */
void	sigint_handler(int sig)
{
	(void)sig;
	exit_status = 130;
	
	ioctl(STDIN_FILENO, TIOCSTI,"\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	//rl_redisplay();
}


void	sigint_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit_status = 130;
	}
}

void	ft_heredoc_handler(int sig)
{
	(void)sig;
	exit_status = 130;
	ioctl(STDIN_FILENO, TIOCSTI,"\n");
	// return ;
	//exit(exit_status);
}

void	ft_sig_term(t_data *data)
{
	//(void)data;
	//ft_clear_history(data);
	close(data->tmp_fd2);
	close(data->tmp_fd);
	write(STDOUT_FILENO, "exit\n", 5);
	free_all(data);
	free_env_list(&data->mini_env);
	exit(0);
}

/** Uses signal function associate to handlers */
void	ft_signals()
{
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}