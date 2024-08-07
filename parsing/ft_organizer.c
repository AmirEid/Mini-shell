/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:43:58 by aeid              #+#    #+#             */
/*   Updated: 2024/08/07 00:48:07 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_organizer_2(t_list **current, t_list **tmp, t_list **tmp2, t_list **redir_tmp, t_tkn_data *string)
{
	*redir_tmp = *current;
	string = (t_tkn_data *)(*current)->content;
	while (*current)
	{
		string = (t_tkn_data *)(*current)->content;
		if (string->type == META_REDIR_IN || string->type == META_REDIR_OUT || string->type == META_APPEND || string->type == META_HEREDOC)
		{
			(*current) = (*current)->next;
			*tmp2 = *current;
			*current = (*current)->next;
		}
		if (!*current || string->type == META_PIPE)
			return ;
		if (string->type == WORD || string->type == COMMAND)
		{
			(*tmp)->next = *current;
			(*tmp2)->next = (*current)->next;
			(*current)->next = *redir_tmp;
			*current = (*redir_tmp)->next;
			break ;
		}
	}
}

static void	ft_set_null(t_tkn_data **string, t_list **tmp, t_list **tmp2, t_list **redir_tmp)
{
	*string = NULL;
	*tmp = NULL;
	*tmp2 = NULL;
	*redir_tmp = NULL;
}

void	ft_organizer(t_list *tokens)
{
	t_list		*current;
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*redir_tmp;
	t_tkn_data	*string;

	current = tokens;
	ft_set_null(&string, &tmp, &tmp2, &redir_tmp);
	while (current)
	{
		string = (t_tkn_data *)current->content;
		while (string->type != META_PIPE)
		{
			if (string->type == META_REDIR_IN || string->type == META_REDIR_OUT || string->type == META_APPEND || string->type == META_HEREDOC)
				ft_organizer_2(&current, &tmp, &tmp2, &redir_tmp, string);
			if (!current || string->type == META_PIPE)
				return ;
			else
				break ;
		}
		tmp = current;
		current = current->next;
	}
}
