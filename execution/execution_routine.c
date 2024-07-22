/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:50:22 by aeid              #+#    #+#             */
/*   Updated: 2024/07/22 16:23:16 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_get_number_of_redirections(t_list *tokens)
{
	t_list		*current;
	t_tkn_data	*tokendata;
	size_t		num_redirs;

	num_redirs = 0;
	current = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == META_REDIR_IN
			|| tokendata->type == META_REDIR_OUT
			|| tokendata->type == META_APPEND
			|| tokendata->type == META_HEREDOC)
			num_redirs++;
		current = current->next;
	}
	return (num_redirs);
}

static void	execute_redirections(t_list *token)
{
	t_list		*current;
	t_tkn_data	*tokendata;

	current = token;
	tokendata = (t_tkn_data *)current->content;
	while (current != NULL && tokendata->type != META_PIPE)
	{
		if (tokendata->type == META_REDIR_IN)
			ft_redir_in(current->next);
		else if (tokendata->type == META_REDIR_OUT)
			ft_redir_out(current->next);
		else if (tokendata->type == META_APPEND)
			ft_redir_append(current->next);
		else if (tokendata->type == META_HEREDOC)
			ft_heredoc(current->next);
		current = current->next;
		tokendata = (t_tkn_data *)current->content;
	}
}

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
		execute_redirections(tokens);
	if (tokendata->type == COMMAND)
		ft_command_execution(tokens, env, current);
	if (tokendata->type == WORD_CD)
		ft_cd(tokens, data);
	if (tokendata->type == WORD_PWD)
		ft_pwd(data);
	if (tokendata->type == WORD_EXPORT)
		ft_export(*data, tokens);
	if (tokendata->type == WORD_UNSET)
		ft_unset(*data, tokens);
		//add here all the builtins @razvan @anouk
}
