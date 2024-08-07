/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:52:40 by aeid              #+#    #+#             */
/*   Updated: 2024/08/07 01:28:23 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static bool ft_get_the_head(t_list **head, t_list **tokens, t_list **prev)
{
    t_list *current;
    t_tkn_data *token_data;

    current = *tokens;
    while (current)
    {
        token_data = (t_tkn_data *)current->content;
        while (token_data->type != META_PIPE)
        {
            token_data = (t_tkn_data *)current->content;
            while (token_data->type == META_REDIR_IN || token_data->type == META_REDIR_OUT || token_data->type == META_APPEND || token_data->type == META_HEREDOC)
            {
                current = current->next;
                *prev = current;
                current = current->next;
                if (!current)
                    return (true);
                token_data = (t_tkn_data *)current->content;
            }
        }
        if (token_data->type == META_PIPE)
            return (false);
        if (token_data->type != META_REDIR_IN || token_data->type != META_REDIR_OUT || token_data->type != META_APPEND || token_data->type != META_HEREDOC)
            *head = current;
        return (false);
    }
}

static void	ft_set_null(t_list **tmp, t_list **redir_tmp)
{
	*tmp = NULL;
	*redir_tmp = NULL;
}

void ft_organizer1(t_list **tokens)
{
	t_list		*current;
	t_list		*prev;
    t_list      *head;

	current = tokens;
	ft_set_null(&prev, &head);
    if (ft_get_the_head(&head, tokens, &prev))
        return ;
    if (head)
    {
        prev->next = head->next;
        head->next = *tokens;
        *tokens = head;
    }
    ft_organizer(*tokens);
}


