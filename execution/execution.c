/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:27:04 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 00:46:53 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static void	ft_assign_args(t_list *args[], t_list *tokens)
{
	t_list		*current;
	t_tkn_data	*tokendata;
	int			i;

	i = 0;
	current = tokens;
	tokendata = NULL;
	if (current == NULL)
		return ;
	args[i] = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		while (tokendata->type != META_PIPE && current != NULL)
		{
			current = current->next;
			if (current != NULL)
				tokendata = (t_tkn_data *)current->content;
		}
		if (tokendata->type == META_PIPE)
		{
			args[++i] = current->next;
			current = current->next;
		}
	}
}

static void	execute_signle_command_line(t_list *tokens, t_list *env, t_data *data, t_types type)
{
	pid_t	pid;

	pid = 0;
	if (type == COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, sigint_exec);
			signal(SIGQUIT, SIG_DFL);
			data->process_num++;
			ft_execute_routine(tokens, env, data);
			free_all(data);
			free_env_list(&env);
			close(data->tmp_fd);
			close(data->tmp_fd2);
			exit(exit_status);
		}
		else
		{
			signal(SIGINT, sigint_exec);
			signal(SIGQUIT, ft_sign_back_slash);
			waitpid(pid, &exit_status, 0);
			printf("exit status child: %d\n", exit_status);
			if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGQUIT)
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
	else
		ft_execute_routine(tokens, env, data);
}


void	ft_execution(t_list *tokens, t_list *env, t_data *data)
{
	t_tkn_data	*tokendata;
	t_list		*args[data->process_num + 1];
	
	if (data->exit_code == -1)
		return ;
	tokendata = (t_tkn_data *)data->tokens->content;
	if (data->process_num < 1)
		return ;
	signal(SIGINT, sigint_exec);
	if (data->process_num > 1)
	{
		ft_assign_args(args, tokens);
		create_pipes_and_execution(args, env, data);
	}
	else
		execute_signle_command_line(tokens, env, data, tokendata->type);
}
