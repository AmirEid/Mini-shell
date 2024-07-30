/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:20:10 by aeid              #+#    #+#             */
/*   Updated: 2024/07/30 15:00:04 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*getTypeName(t_types type)
{
	switch (type)
	{
		case SPECIAL_SQUOTE: return "SPECIAL_SQUOTE";
		case SPECIAL_DQUOTE: return "SPECIAL_DQUOTE";
		case META_DOL: return "META_DOL";
		case META_PIPE: return "META_PIPE";
		case META_REDIR_IN: return "META_REDIR_IN";
		case META_REDIR_OUT: return "META_REDIR_OUT";
		case META_APPEND: return "META_APPEND";
		case META_HEREDOC: return "META_HEREDOC";
		case WORD_EXPORT: return "WORD_EXPORT";
		case WORD_UNSET: return "WORD_UNSET";
		case WORD_ENV: return "WORD_ENV";
		case WORD_ECHO: return "WORD_ECHO";
		case WORD_CD: return "WORD_CD";
		case WORD_EXIT: return "WORD_EXIT";
		case WORD_PWD: return "WORD_PWD";
		case WORD_DOL: return "WORD_DOL";
		case WORD: return "WORD";
		case COMMAND: return "COMMAND";
		case WORD_WITH_DQUOTE_INSIDE: return "WORD_WITH_DQUOTE_INSIDE";
		case WORD_WITH_SQUOTE_INSIDE: return "WORD_WITH_SQUOTE_INSIDE";
		default: return "UNKNOWN_TYPE";
    }
}

static int	ft_check_next_token(t_list *current, t_tkn_data *string, t_data *data)
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
			return(-1);
		}
		next = (t_tkn_data *)current->next->content;
		if (string->type != META_PIPE && next->type == META_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return(-1);
		}
		if (next->type == string->type)
		{
			if (string->type == META_PIPE)
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
						2);
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
						2);
			return(-1);
		}
		if ((next->type == META_HEREDOC && string->type == META_PIPE) || (next->type == META_PIPE && string->type == META_HEREDOC))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return(-1);
		}
		if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT
			|| string->type == META_APPEND || string->type == META_HEREDOC)
			&& (next->type != WORD && next->type != META_DOL))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
				write (2, "'", 1);
				write(2, next->token, ft_strlen(next->token));
				write (2, "'", 1);
				ft_putstr_fd("\n", 2);
				return(-1);
			}
		if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT
			|| string->type == META_APPEND || string->type == META_HEREDOC)
			&& (data->exp_var == 1))
			{
				ft_putstr_fd("minishell: ", 2);
				write (2, "'", 1);
				write(2, next->token, ft_strlen(next->token));
				write (2, "'", 1);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return(-1);
			}
	}
	return(0);
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

void	ft_parser(t_list *tokens, t_data *data)
{
	t_list		*current;
	t_tkn_data	*string;

	current = tokens;
	string = (t_tkn_data *)current->content;
	if (string->type == META_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		exit_status = -1;
		return;
	}
	while (current)
	{
		string = (t_tkn_data *)current->content;
		exit_status = ft_check_next_token(current, string, data);
		if (exit_status == -1)
			return ;
		current = current->next;
	}
	ft_organizer(tokens);
}
