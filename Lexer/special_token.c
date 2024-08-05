/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:38:30 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:25:27 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static char	*special_token_handler(t_data *data, t_tkn_data *token, int *quote_flag)
{
	if (data->args[data->start] == '\'')
	{
		while (data->args[data->current] && data->args[data->current] != '\'')
			(data->current)++;
		if (data->args[data->current] == '\'')
			(*quote_flag)++;
	}
	else
	{
		while (data->args[data->current] && data->args[data->current] != '\"')
		{
			if (data->args[data->current] == '$')
				get_variable_len(data, data->current, &token->variable_len);
			(data->current)++;
		}
		if (data->args[data->current] == '\"')
			(*quote_flag)++;
	}
	if (data->args[data->current])
		(data->current)++;
	return (ft_substr(data->args, data->start + 1, data->current - data->start - 2));
}

static void	ft_assigning(t_tkn_data **token, int *quote_flag, t_types type)
{
	(*token)->type = type;
	(*token)->token = NULL;
	(*token)->variable_len = 0;
	(*token)->cmd_exec_path = NULL;
	(*quote_flag) = 0;
}

static void	ft_quote_handler(t_data **data, t_tkn_data **token, int *quote_flag, char **tmp)
{
	(*quote_flag)++;
	((*data)->current)++;
	(*tmp) = special_token_handler(*data, *token, quote_flag);
}

static void	else_handler(t_data **data, t_tkn_data **token, char **tmp)
{
	while (ft_isprint((*data)->args[(*data)->current]) && !ft_isquote((*data)->args[(*data)->current]))
	{
		if ((*data)->args[(*data)->current] == '$')
			get_variable_len(*data, (*data)->current, &(*token)->variable_len);
		((*data)->current)++;
	}
	(*tmp) = ft_substr((*data)->args, (*data)->start, (*data)->current - (*data)->start);
}

static int	ft_unclosed_quote_error(int quote_flag, t_data **data)
{
	if (quote_flag % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		(*data)->exit_code = -1;
		exit_status = -1;
		return (-1);
	}
	return (0);
}


int	ft_special_token(t_data *data, t_types type)
{
	t_list		*node;
	t_tkn_data	*token;
	char		*tmp;
	int			quote_flag;

	memory_allocator((void **)&node, sizeof(t_list), data);
	memory_allocator((void **)&token, sizeof(t_tkn_data), data);
	ft_assigning(&token, &quote_flag, type);
	while (data->args[data->current] && ft_isprint(data->args[data->current]))
	{
		if (ft_isquote(data->args[data->start]))
			ft_quote_handler(&data, &token, &quote_flag, &tmp);
		else
			else_handler(&data, &token, &tmp);
		token->token = ft_strjoin(token->token, tmp);
		free(tmp);
		data->start = data->current;
	}
	if (ft_unclosed_quote_error(quote_flag, &data) == -1)
		return (-1);
	node->content = token;
	node->next = NULL;
	ft_lstadd_back(&data->tokens, node);
	if (data->args[data->current] == '\0')
		data->current--;
	return (exit_status);
}


// int ft_special_token(t_data *data, t_types type)
// {
// 	t_list *node;
// 	t_tkn_data *token;
// 	char *tmp;
// 	int quote_flag;

// 	memory_allocator((void **)&node, sizeof(t_list), data);
// 	memory_allocator((void **)&token, sizeof(t_tkn_data), data);
// 	token->type = type;
// 	token->token = NULL;
// 	token->variable_len = 0;
// 	token->cmd_exec_path = NULL;
// 	quote_flag = 0;
// 	while (data->args[data->current] && ft_isprint(data->args[data->current]))
// 	{
// 		if (ft_isquote(data->args[data->start]))
// 		{
// 			quote_flag++;
// 			(data->current)++;
// 			tmp = special_token_handler(data, token, &quote_flag);	
// 		}
// 		else
// 		{
// 			while (ft_isprint(data->args[data->current]) && !ft_isquote(data->args[data->current]))
// 			{
// 				if (data->args[data->current] == '$')
// 					get_variable_len(data, data->current, &token->variable_len);
// 				(data->current)++;
// 			}
// 			tmp = ft_substr(data->args, data->start, data->current - data->start);
// 		}
// 		token->token = ft_strjoin(token->token, tmp);
// 		free(tmp);
// 		data->start = data->current;
// 	}
// 	if (quote_flag % 2 != 0)
// 	{
// 		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
// 		return (-1);
// 	}
// 	node->content = token;
// 	node->next = NULL;
// 	ft_lstadd_back(&data->tokens, node);
// 	return (0);
// }