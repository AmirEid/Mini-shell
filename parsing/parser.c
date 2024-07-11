/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:20:10 by aeid              #+#    #+#             */
/*   Updated: 2024/07/11 16:42:46 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_check_next_token(t_list *current, t_tkn_data *string)
{
	t_tkn_data	*next;

	next = NULL;
	if (string->type == META_PIPE || string->type == META_REDIR_IN
		|| string->type == META_REDIR_OUT || string->type == META_APPEND
		|| string->type == META_HEREDOC)
	{
		if (!current->next)
		{
			if (string->type == META_PIPE)
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
						2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
						2);
			exit(2);
		}
		next = (t_tkn_data *)current->next->content;
		if (string->type != META_PIPE && next->type == META_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			exit(2);
		}
		if (next->type == string->type)
		{
			if (string->type == META_PIPE)
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
						2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
						2);
			exit(2);
		}
		if ((next->type == META_HEREDOC && string->type == META_PIPE) || (next->type == META_PIPE && string->type == META_HEREDOC))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			exit(2);
		}
	}
}

static void	ft_organizer(t_list *tokens)
{
	t_list		*current;
	t_list		*tmp;
	t_list		*tmp2;
	t_list		*redir_tmp;
	t_tkn_data	*string;

	current = tokens;
	string = NULL;
	tmp2 = NULL;
	redir_tmp = NULL;
	tmp = NULL;
	while (current)
	{
		string = (t_tkn_data *)current->content;
		while (string->type != META_PIPE)
		{
			if (string->type == META_REDIR_IN || string->type == META_REDIR_OUT
				|| string->type == META_APPEND || string->type == META_HEREDOC)
			{
				redir_tmp = current;
				while (current)
				{
					string = (t_tkn_data *)current->content;
					if (string->type == META_REDIR_IN || string->type == META_REDIR_OUT
						|| string->type == META_APPEND || string->type == META_HEREDOC)
						{
							current = current->next;
							tmp2 = current;
							current = current->next;
						}
					if (!current || string->type == META_PIPE)
						return ;
					if (string->type == WORD || string->type == COMMAND)
					{
						tmp->next = current;
						tmp2->next = current->next;
						current->next = redir_tmp;
						current = redir_tmp->next;
						break ;
					}
				}
			}
			else
				break ;
		}
		tmp = current;
		current = current->next;
		//printTokens(tokens);
		//printf("\n");
	}
}

//echo 1=2 < inf > out here=3 > out

void	ft_parser(t_list *tokens)
{
	t_list		*current;
	t_tkn_data	*string;

	current = tokens;
	string = (t_tkn_data *)current->content;
	if (string->type == META_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		exit(2);
	}
	while (current)
	{
		string = (t_tkn_data *)current->content;
		ft_check_next_token(current, string);
		current = current->next;
	}
	ft_organizer(tokens);
}
