/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:27:04 by aeid              #+#    #+#             */
/*   Updated: 2024/07/26 00:12:30 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static int ft_get_process_num(t_list *tokens)
{
	t_list *current;
	t_tkn_data *tokendata;
	int process_num;

	process_num = 0;
	current = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == META_PIPE)
			process_num++;
		current = current->next;
	}
	return (process_num + 1);
}

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
void ft_execution(t_list *tokens, t_list *env, t_data *data)
{
	t_tkn_data *tokendata;
	int process_num;
	t_list *args[MAX_PROCESS_NUM + 1];
	pid_t pid;
	
	if (data->exit_status == -1)
		return ;
	tokendata = (t_tkn_data *)data->tokens->content;
	pid = 0;
	process_num = ft_get_process_num(tokens);
	if (process_num < 1 || process_num > MAX_PROCESS_NUM)
		return ;
	args[process_num + 1] = NULL;
	if (process_num > 1)
	{
		ft_assign_args(args, tokens);
		create_pipes_and_execution(args, process_num, env, data);
	}
	else
	{
		if (tokendata->type == COMMAND)
		{
			pid = fork();
			if (pid == 0)
				ft_execute_routine(tokens, env, data);
			else
				waitpid(pid, NULL, 0);
		}
		else
			ft_execute_routine(tokens, env, data);
		
	}
}
