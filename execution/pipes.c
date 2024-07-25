/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:25:02 by aeid              #+#    #+#             */
/*   Updated: 2024/07/25 23:09:51 by aeid             ###   ########.fr       */
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

// there is an issue with closing the pipes.
void create_pipes_and_execution(t_list *args[], int process_num, t_list *env, t_data *data)
{
	int pipe_fd[(process_num - 1) * 2];
	int i;
	pid_t pid;
	
	i = -1;
	pid = 0;
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
			printf("pid: %d, process_num: %d\n", getpid(), process_num);
			close_pipes(pipe_fd, process_num);
			ft_execute_routine(args[i], env, data);
			exit(0);
		}
	}
	//this should be the parent process where it waits for all the children 
	//to finish using waitpid, checking the exit status and do the free
	close_pipes(pipe_fd, process_num);
	while(process_num--)
		wait(NULL);
}
