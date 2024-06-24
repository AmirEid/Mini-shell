/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:10:35 by aeid              #+#    #+#             */
/*   Updated: 2024/06/23 00:55:13 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"
//shortcut: token->token could replace string..and there is no need for string.

static void copy_assign(char *string, t_data *data, t_tkn_data *token, t_list *node)
{
	token->token = string;
	node->content = token;
	node->next = NULL;
	ft_lstadd_back(&data->tokens, node);
}

static void  ft_copier(int *i, int c, char *string, t_data *data, int *quote_flag)
{
	int len;
	
	len = data->current - data->start - *quote_flag;
	while (*i < len && *quote_flag != 0)
	{
		(data->start)++;
		(*quote_flag)--;
		while (data->args[data->start + *i] != c && data->args[data->start + *i] != '\0')
		{
			string[*i] = data->args[data->start + *i];
			(*i)++;
		}
	}
}

void quote_removal_copy(char *string, t_data *data, t_tkn_data *token, t_list *node, int quote_flag)
{
	int len;
	int i;

	len = data->current - data->start - quote_flag;
	i = 0;
	memory_allocator((void **)&string, len + 1);
	while (i < len && quote_flag != 0)
	{
		if (data->args[data->start + i] == '\"')
		{
			ft_copier(&i, '\"', string, data, &quote_flag);
			if (token->type != WORD_DOL)
				token->type = WORD_WITH_DQUOTE_INSIDE;
		}
		else if (data->args[data->start + i] == '\'') 
			ft_copier(&i, '\'', string, data, &quote_flag);
		else
		{
			string[i] = data->args[data->start + i];
			i++;
		}
	}
	string[i] = '\0';
	copy_assign(string, data, token, node);
}

int static ft_checker(t_data *data, int *quote_flag, t_tkn_data *token)
{
	if (!ft_isprint(data->args[data->current]) && !(*quote_flag % 2))
		return (1);
	else if (ft_ismeta(data->args[data->current]) && !(*quote_flag % 2))
		return (1);
	else if (data->args[data->current] == '$')
	{
		token->type = WORD_DOL;
		get_variable_len(data, data->current, &token->variable_len);
		if (token->variable_len == 0 && data->args[data->current + 1] == '\"')
				token->variable_len++;
	}
	else if (data->args[data->current] == '\"')
	{
		(*quote_flag)++;
		(data->current)++;
		while (data->args[data->current] != '\"')
		{
			if (data->args[data->current] == '$')
				get_variable_len(data, data->current, &token->variable_len);
			(data->current)++;
		}
		if (data->args[data->current] == '\"')
			(*quote_flag)++;
		if (ft_isprint(data->args[data->current + 1]) && !ft_ismeta(data->args[data->current + 1]) && data->args[data->current + 1] != '$')
		{
			(data->current)++;
			while (ft_isprint(data->args[data->current]) && !ft_ismeta(data->args[data->current]) && data->args[data->current] != '$' && data->args[data->current] != '\0')
				(data->current)++;
			return (1);
		}
	}
	else if (data->args[data->current] == '\'')
	{
		(*quote_flag)++;
		(data->current)++;
		while (data->args[data->current] != '\'')
			(data->current)++;
		if (data->args[data->current] == '\'')
			(*quote_flag)++;
	}
	return (0);
}

void ft_word_token(t_data *data, t_types type)
{
	t_list *node;
	char *string;
	t_tkn_data *token;
	int quote_flag;
	
	memory_allocator((void **)&node, sizeof(t_list));
	memory_allocator((void **)&token, sizeof(t_tkn_data));
	quote_flag = 0;
	token->type = type;
	token->variable_len = 0;
	string = NULL;
	while (data->args[data->current])
	{
		if (ft_checker(data, &quote_flag, token))
			break ;
		(data->current)++; 
	}
	if (!(quote_flag % 2) && quote_flag != 0)
		quote_removal_copy(string, data, token, node, quote_flag);
	else
	{
		string = ft_substr(data->args, data->start, data->current - data->start);
		copy_assign(string, data, token, node);;
	}
	(data->current)--;
}

