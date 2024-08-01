/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:59 by anoukmourna       #+#    #+#             */
/*   Updated: 2024/08/01 19:32:04 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./headers/minishell.h"

/** Signal handler for the SIGINT signal (ctrl+c) */
void	sigint_handler(int sig)
{
	(void)sig;
	exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}



//anouk, possiamo usare solo un globale per l'exit code 
/** Signal handler for the SIGINT signal inside a heredoc (ctrl+c) */

void	ft_heredoc_handler(int sig)
{
	(void)sig;
	printf("\n");
	exit_status = 130;
	exit(exit_status);
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
void	ft_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}