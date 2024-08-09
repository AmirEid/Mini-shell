/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:25:02 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 13:18:38 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static void	create_pipes(int pipe_fd[], int process_num)
{
	int	i;

	i = 0;
	while(i < process_num - 1)
	{
		if (pipe(pipe_fd + i * 2) == -1)
			return ;
			//handle errors here
		i++;
	}
}

void	close_pipes(int pipe_fd[], int process_num)
{
	int	i;

	i = -1;
	while (++i < 2 * (process_num - 1))
	{
		close(pipe_fd[i]);
	}
}

static bool	ft_check_here_doc(t_list *list)
{
	t_list	*current;
	t_tkn_data	*tokendata;

	current = list;
	tokendata = (t_tkn_data *)current->content;
	while (current != NULL && tokendata->type != META_PIPE)
	{
		if (tokendata->type == META_HEREDOC)
			return (true);
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
	return (false);
}

// there is an issue with closing the pipes.
void	create_pipes_and_execution(t_list *args[], t_list *env, t_data *data)
{
	int		pipe_fd[(data->process_num - 1) * 2];
	int		i;
	pid_t	pid;
	pid_t	pids[data->process_num];
	bool	wait_for[data->process_num];

	i = -1;
	pid = 0;
	while (++i < data->process_num)
		wait_for[i] = true;
	i = -1;
	create_pipes(pipe_fd, data->process_num);
	while (++i < data->process_num)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, sigint_exec);
			signal(SIGQUIT, SIG_DFL);
			if (i == 0)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], 1);
			}
			else if (i == data->process_num - 1)
			{
				close(pipe_fd[(i - 1) * 2 + 1]);
				dup2(pipe_fd[(i - 1) * 2], 0);
			}
			else
			{
				close(pipe_fd[(i - 1) * 2 + 1]);
				dup2(pipe_fd[(i - 1) * 2], 0);
				close(pipe_fd[i * 2]);
				dup2(pipe_fd[i * 2 + 1], 1);
			}
			close_pipes(pipe_fd, data->process_num);
			ft_execute_routine(args[i], env, data);
			free_all(data);
			free_env_list(&env);
			close(data->tmp_fd);
			close(data->tmp_fd2);
			exit(exit_status);
		}
		pids[i] = pid;
		if (ft_check_here_doc(args[i]))
		{
			waitpid(pid, &exit_status, 0);
			exit_status = exit_status / 256;
			wait_for[i] = false;
		}
	}
	close_pipes(pipe_fd, data->process_num);
	i = -1;
	while(++i < data->process_num)
	{
		if (wait_for[i])
        {
			signal(SIGINT, sigint_exec);
			signal(SIGQUIT, ft_sign_back_slash);
			waitpid(pids[i], &exit_status, 0);
			if ((i == data->process_num - 1) && WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGQUIT)
			{
				write(1, "Quit (core dumped)\n", 19);
				exit_status = 131;
			}
			if (exit_status == SIGINT)
				exit_status = 130;
			else
				exit_status = exit_status / 256;
        }	
	}			
}
