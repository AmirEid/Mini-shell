/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:50:22 by aeid              #+#    #+#             */
/*   Updated: 2024/07/28 19:47:44 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void execution_redir_in(t_list *token, t_list *env, t_data *data, int *redi_num)
{
	t_list *current;
	t_tkn_data *tokendata;
	
	current = token;
	tokendata = (t_tkn_data *)current->content;
	if (*redi_num == 0)
		return ;
	while (current != NULL && tokendata->type != META_PIPE && *redi_num)
	{
		if (tokendata->type == META_REDIR_IN)
			ft_redir_in(current->next, redi_num);
		else if (tokendata->type == META_HEREDOC)
			ft_heredoc(current->next, env, data, redi_num);
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
}

static void execution_redir_out(t_list *token, int *redi_num)
{
	t_list *current;
	t_tkn_data *tokendata;
	
	current = token;
	tokendata = (t_tkn_data *)current->content;
	if (*redi_num == 0)
		return ;
	while (current != NULL && tokendata->type != META_PIPE && *redi_num)
	{
		if (tokendata->type == META_REDIR_OUT)
			ft_redir_out(current->next, redi_num);
		else if (tokendata->type == META_APPEND)
			ft_redir_append(current->next, redi_num);
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
}

static void	execute_redirections(t_list *token, t_list *env, t_data *data)
{
	int redi_in_num;
	int redi_out_num;

	redi_in_num = ft_get_number_of_redir_in_or_out(token, META_REDIR_IN, META_HEREDOC);
	redi_out_num = ft_get_number_of_redir_in_or_out(token, META_REDIR_OUT, META_APPEND);
	execution_redir_in(token, env, data, &redi_in_num);
	execution_redir_out(token, &redi_out_num);
}

//there is a mistake, execute the first redirection, then command then the rest
// of the redirections.


void	ft_execute_routine(t_list *tokens, t_list *env, t_data *data)
{
	t_list *current;
	t_tkn_data *tokendata;
	size_t num_redirs;
	//THIS IS WORK IN PROGRESS
	//in this function i should iterate over the list, until pipe or null..
	//the function will call different functions depending on the type of the token. >> > < << external,
		//builtin
	//make sure to do invoke execve in the end of the function,
		//execute first all builtins and redirections first, then
	//execute the external command.
	// a process can only hand one command (external or builtin) at a time,
		//with redirections.
	current = tokens;
	num_redirs = ft_get_number_of_redirections(tokens);
	tokendata = (t_tkn_data *)current->content;
	if (num_redirs > 0)
		execute_redirections(tokens, env, data);
	if (tokendata->type == COMMAND)
		ft_command_execution(tokens, env, current, data);
	else if (tokendata->type == WORD_CD)
		ft_cd(tokens, data);
	else if (tokendata->type == WORD_PWD)
		ft_pwd(data);
	else if (tokendata->type == WORD_EXPORT)
		ft_export(*data, tokens);
	else if (tokendata->type == WORD_ECHO)
		ft_echo(tokens);
	else if (tokendata->type == WORD_EXIT)
		ft_exit(tokens);
	else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tokendata->token, 2);
			ft_putstr_fd(": command not found\n", 2);
			//free_all(data);
			data->exit_status = 127;
		}
	//add here all the builtins @razvan @anouk
}
