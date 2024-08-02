/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:27:04 by aeid              #+#    #+#             */
/*   Updated: 2024/08/02 12:10:50 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static void ft_assign_args(t_list *args[], t_list *tokens)
{
	t_list *current;
	t_tkn_data *tokendata;
	int i;

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

	// static void printargs(t_list *args[], int process_num) 
	// {
	// 	int i;
	// 	t_tkn_data *tokendata;

	// 	i = 0;
	// 	tokendata = NULL;
	// 	while (i < process_num)
	// 	{
	// 		tokendata = (t_tkn_data *)args[i]->content;
	// 		printf("args[%d]: %s\n", i, tokendata->token);
	// 		i++;
	// 	}
	// }

//I changed t_list **args because there is no need to allocate memory and we already know/
//the number of processes we have to create. We can just pass the array of pointers to the functions.

static void execute_signle_command_line(t_list *tokens, t_list *env, t_data *data, t_types type)
{
	pid_t pid;

	pid = 0;
	if (type == COMMAND)
	{
		pid = fork();
		if (pid == 0)
		{
			data->process_num++;
			ft_execute_routine(tokens, env, data);
		}
		else
		{
			waitpid(pid, &exit_status, 0);
			exit_status = exit_status / 256;
		}	
	}
	else
		ft_execute_routine(tokens, env, data);
}

// static void clear_args(t_list *args[], int size) {
//     for (int i = 0; i < size; i++) {
//         args[i] = NULL; // Reset pointers to NULL
//     }
// }

//TO do list: add the process number in the data struct, so we can use it in the waitpid or not wait pid;


void ft_execution(t_list *tokens, t_list *env, t_data *data)
{
	t_tkn_data *tokendata;
	t_list *args[data->process_num + 1];
	
	//clear_args(args, MAX_PROCESS_NUM + 1);
	if (data->exit_code == -1)
		return ;
	tokendata = (t_tkn_data *)data->tokens->content;
	if (data->process_num < 1)
		return ;
	//args[data->process_num] = NULL;
	if (data->process_num > 1)
	{
		ft_assign_args(args, tokens);
		create_pipes_and_execution(args, env, data);
	}
	else
		execute_signle_command_line(tokens, env, data, tokendata->type);
}
