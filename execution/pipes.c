/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:25:02 by aeid              #+#    #+#             */
/*   Updated: 2024/07/31 13:53:18 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static void create_pipes(int pipe_fd[], int process_num)
{
	int i;
	
	i = 0;
	while(i < process_num - 1)
	{
		if (pipe(pipe_fd + i * 2) == -1)
			return ;
			//handle errors here
		i++;
	}
}

void close_pipes(int pipe_fd[], int process_num)
{
	int i;
	
	i = -1;
	while (++i < 2 * (process_num - 1))
	{
		close(pipe_fd[i]);
	}
}

static bool ft_check_here_doc(t_list *list)
{
	t_list *current;
	t_tkn_data *tokendata;
	
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
void create_pipes_and_execution(t_list *args[], int process_num, t_list *env, t_data *data)
{
	int pipe_fd[(process_num - 1) * 2];
	int i;
	pid_t pid;
	pid_t pids[process_num];
	bool wait_for[process_num];
	
	i = -1;
	pid = 0;
	//maybe put this in the intialization of the data struct
	data->tmp_fd = dup(0);
	while (++i < process_num)
		wait_for[i] = true;
	i = -1;
	create_pipes(pipe_fd, process_num);
	while (++i < process_num)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], 1);
			}
			else if (i == process_num - 1)
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
			close_pipes(pipe_fd, process_num);
			ft_execute_routine(args[i], env, data);
			exit(0);
		}
		pids[i] = pid;
		if (ft_check_here_doc(args[i]))
		{
			waitpid(pid, NULL, 0);
			wait_for[i] = false;
		}
	}
	close_pipes(pipe_fd, process_num);
	i = -1;
	while(++i < process_num)
		if (wait_for[i])
			waitpid(pids[i], NULL, 0);
			
}
