/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:20:10 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:40:33 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	check_initial_conditions(t_list *current, t_tkn_data *string)
{
	if (!current->next)
	{
		if (string->type == META_PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	return (0);
}

static int	check_next_token_conditions(t_tkn_data *string, t_tkn_data *next)
{
	if (string->type != META_PIPE && next->type == META_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	if (next->type == string->type)
	{
		if (string->type == META_PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, next->token, ft_strlen(next->token));
			ft_putstr_fd("'\n", 2);
		}
		return (-1);
	}
	if (next->type == META_PIPE && string->type == META_HEREDOC)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	return (0);
}

static int	check_ambiguous_redirect(t_tkn_data *string, t_tkn_data *next, t_data *data)
{
	if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT ||
		 string->type == META_APPEND || string->type == META_HEREDOC) &&
		(next->type != WORD && next->type != META_DOL))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		write(2, "'", 1);
		write(2, next->token, ft_strlen(next->token));
		write(2, "'", 1);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT || string->type == META_APPEND) && (data->exp_var == 1))
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, "'", 1);
		write(2, next->token, ft_strlen(next->token));
		write(2, "'", 1);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (-1);
	}
	return (0);
}

static int	ft_check_next_token(t_list *current, t_tkn_data *string, t_data *data)
{
	t_tkn_data	*next;

	next = NULL;
	if (string->type == META_PIPE || string->type == META_REDIR_IN ||
		string->type == META_REDIR_OUT || string->type == META_APPEND ||
		string->type == META_HEREDOC)
	{
		if (check_initial_conditions(current, string) == -1)
			return (1);
		next = (t_tkn_data *)current->next->content;
		if (check_next_token_conditions(string, next) == -1)
			return (2);
		if (check_ambiguous_redirect(string, next, data) == -1)
			return (1);
	}
	return (0);
}

// static int	ft_check_next_token(t_list *current, t_tkn_data *string, t_data *data)
// {
// 	t_tkn_data	*next;

// 	next = NULL;
// 	if (string->type == META_PIPE || string->type == META_REDIR_IN
// 		|| string->type == META_REDIR_OUT || string->type == META_APPEND
// 		|| string->type == META_HEREDOC)
// 	{
// 		if (!current->next)
// 		{
// 			if (string->type == META_PIPE)
// 				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
// 						2);
// 			else
// 				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
// 						2);
// 			return(-1);
// 		}
// 		next = (t_tkn_data *)current->next->content;
// 		if (string->type != META_PIPE && next->type == META_PIPE)
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
// 			return(-1);
// 		}
// 		if (next->type == string->type)
// 		{
// 			if (string->type == META_PIPE)
// 				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
// 						2);
// 			else
// 				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
// 						2);
// 			return(-1);
// 		}
// 		if ((next->type == META_HEREDOC && string->type == META_PIPE) || (next->type == META_PIPE && string->type == META_HEREDOC))
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
// 			return(-1);
// 		}
// 		if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT
// 			|| string->type == META_APPEND || string->type == META_HEREDOC)
// 			&& (next->type != WORD && next->type != META_DOL))
// 			{
// 				ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
// 				write (2, "'", 1);
// 				write(2, next->token, ft_strlen(next->token));
// 				write (2, "'", 1);
// 				ft_putstr_fd("\n", 2);
// 				return(-1);
// 			}
// 		if ((string->type == META_REDIR_IN || string->type == META_REDIR_OUT
// 			|| string->type == META_APPEND || string->type == META_HEREDOC)
// 			&& (data->exp_var == 1))
// 			{
// 				ft_putstr_fd("minishell: ", 2);
// 				write (2, "'", 1);
// 				write(2, next->token, ft_strlen(next->token));
// 				write (2, "'", 1);
// 				ft_putstr_fd(": ambiguous redirect\n", 2);
// 				return(-1);
// 			}
// 	}
// 	return(0);
// }

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

static void	ft_organizer(t_list *tokens)
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

//echo 1=2 < inf > out here=3 > out

void	ft_parser(t_list *tokens, t_data *data)
{
	t_list		*current;
	t_tkn_data	*string;
	int			status;

	current = tokens;
	string = (t_tkn_data *)current->content;
	if (string->type == META_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		data->exit_code = -1;
		exit_status = 2; //ok
		return ;
	}
	while (current)
	{
		string = (t_tkn_data *)current->content;
		status = ft_check_next_token(current, string, data);
		if (status != 0)
		{
			data->exit_code = -1;
			exit_status = status;
			return ;
		}
		current = current->next;
	}
	ft_organizer(tokens);
}
