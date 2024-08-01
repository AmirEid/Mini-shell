/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rout_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:36:24 by aeid              #+#    #+#             */
/*   Updated: 2024/07/27 22:21:16 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_get_number_of_redirections(t_list *tokens)
{
	t_list		*current;
	t_tkn_data	*tokendata;
	size_t		num_redirs;

	num_redirs = 0;
	current = tokens;
	tokendata = (t_tkn_data *)current->content;
	while (current != NULL && tokendata->type != META_PIPE)
	{
		if (tokendata->type == META_REDIR_IN
			|| tokendata->type == META_REDIR_OUT
			|| tokendata->type == META_APPEND
			|| tokendata->type == META_HEREDOC)
			num_redirs++;
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
	return (num_redirs);
}

int	ft_get_number_of_redir_in_or_out(t_list *tokens, t_types type1, t_types type2)
{
	t_list		*current;
	t_tkn_data	*tokendata;
	size_t		num_redirs;

	num_redirs = 0;
	current = tokens;
	tokendata = (t_tkn_data *)current->content;
	while (current != NULL && tokendata->type != META_PIPE)
	{
		if (tokendata->type == type1 || tokendata->type == type2)
			num_redirs++;
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
	return (num_redirs);
}