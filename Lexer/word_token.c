/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:10:35 by aeid              #+#    #+#             */
/*   Updated: 2024/07/30 22:00:41 by aeid             ###   ########.fr       */
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

static int dollar_counter(char *args, int current)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < current)
	{
		if (args[i] == '$' && ft_isquote(args[i + 1]))
			count++;
		i++;
	}
	return (count);
}

/*static void  ft_copier(int *i, int c, char *string, t_data *data, int *quote_flag)
{
	int len;
	int dol_count;
	
	dol_count = dollar_counter(data->args, data->current);
	len = data->current - data->start - *quote_flag - dol_count;
	while (*i < (len + dol_count) && *quote_flag != 0)
	{
		(data->start)++;
		(*quote_flag)--;
		while (data->args[data->start + *i] != c && data->args[data->start + *i] != '\0')
		{
			if (dol_count && ft_isquote(data->args[data->start + *i + 1]))
			{
				string[*i - 1] = data->args[data->start + *i];
				(*i)++;
				return ;
			}
			else
				string[*i] = data->args[data->start + *i];
			(*i)++;
		}
	}
}*/

static void  ft_copier(int *i, int c, char *string, t_data *data, int *quote_flag)
{
	(data->start)++;
	(*quote_flag)--;
	while (data->args[data->start + *i] != c && data->args[data->start + *i] != '\0')
	{
		string[*i] = data->args[data->start + *i];
		(*i)++;
	}
	(data->start)++;
	(*quote_flag)--;
}

static void  ft_copier_dol(int *i, int c, char *string, t_data *data, int *quote_flag)
{
	(data->start)++;
	(*quote_flag)--;
	while (data->args[data->start + *i] == c && data->args[data->start + *i] != '\0')
	{
		(data->start)++;
		(*quote_flag)--;
	}
	while (data->args[data->start + *i] != c && data->args[data->start + *i] != '\0')
	{
		string[*i] = data->args[data->start + *i];
		(*i)++;
	}
	(data->start)++;
	(*quote_flag)--;
}

static void dquote_removal_handler(char **string, t_data **data, t_tkn_data **token, int *q_flag, int *i)
{
	ft_copier(i, '\"', *string, *data, q_flag);
	if ((*token)->type != WORD_DOL)
		(*token)->type = WORD_WITH_DQUOTE_INSIDE;
}

static void squote_removal_handler(char **string, t_data **data, t_tkn_data **token, int *q_flag, int *i)
{
	ft_copier(i, '\'', *string, *data, q_flag);
	(*token)->type = WORD_WITH_SQUOTE_INSIDE;
}

static void else_handler(char **string, t_data **data, int *i)
{
	(*string)[*i] = (*data)->args[(*data)->start + *i];
	(*i)++;
}

void quote_removal_copy(char *string, t_data *data, t_tkn_data *token, t_list *node, int quote_flag)
{
	int len;
	int i;
	int dol_count;

	dol_count = dollar_counter(data->args, data->current);
	len = data->current - data->start - quote_flag - dol_count;
	i = 0;
	memory_allocator((void **)&string, len + 1, data);
	while (i < (len + dol_count))
	{
		if (data->args[data->start + i] == '$' && ft_isquote(data->args[data->start + i + 1]))
			ft_copier_dol(&i, data->args[data->start + i + 1], string, data, &quote_flag);
		else if (data->args[data->start + i] == '\"')
			dquote_removal_handler(&string, &data, &token, &quote_flag, &i);
		else if (data->args[data->start + i] == '\'') 
			squote_removal_handler(&string, &data, &token, &quote_flag, &i);
		else
			else_handler(&string, &data, &i);
	}
	string[i] = '\0';
	if (data->args[data->start + i] == '\"')
		token->type = WORD_WITH_DQUOTE_INSIDE;
	if (data->args[data->start + i] == '\'')
		token->type = WORD_WITH_SQUOTE_INSIDE;
	copy_assign(string, data, token, node);
}

// void quote_removal_copy(char *string, t_data *data, t_tkn_data *token, t_list *node, int quote_flag)
// {
// 	int len;
// 	int i;
// 	int dol_count;

// 	dol_count = dollar_counter(data->args, data->current);
// 	len = data->current - data->start - quote_flag - dol_count;
// 	i = 0;
// 	memory_allocator((void **)&string, len + 1, data);
// 	while (i < (len + dol_count))
// 	{
// 		if (data->args[data->start + i] == '$' && ft_isquote(data->args[data->start + i + 1]))
// 			ft_copier_dol(&i, data->args[data->start + i + 1], string, data, &quote_flag);
// 		else if (data->args[data->start + i] == '\"')
// 		{
// 			ft_copier(&i, '\"', string, data, &quote_flag);
// 			if (token->type != WORD_DOL)
// 				token->type = WORD_WITH_DQUOTE_INSIDE;
// 		}
// 		else if (data->args[data->start + i] == '\'') 
// 		{
// 			ft_copier(&i, '\'', string, data, &quote_flag);
// 			token->type = WORD_WITH_SQUOTE_INSIDE;
// 		}
// 		else
// 		{
// 			string[i] = data->args[data->start + i];
// 			i++;
// 		}
// 	}
// 	string[i] = '\0';
// 	if (data->args[data->start + i] == '\"')
// 		token->type = WORD_WITH_DQUOTE_INSIDE;
// 	if (data->args[data->start + i] == '\'')
// 		token->type = WORD_WITH_SQUOTE_INSIDE;
// 	copy_assign(string, data, token, node);
// }

static int dquote_checker_handler(t_data **data, t_tkn_data **token, int *quote_flag)
{
	(*quote_flag)++;
	((*data)->current)++;
	while ((*data)->args[(*data)->current] != '\"' && (*data)->args[(*data)->current] != '\0')
	{
		if ((*data)->args[(*data)->current] == '$')
			get_variable_len(*data, (*data)->current, &(*token)->variable_len);
		((*data)->current)++;
	}
	if ((*data)->args[(*data)->current] == '\"')
		(*quote_flag)++;
	if ((*data)->args[(*data)->current] && ft_isprint((*data)->args[(*data)->current + 1]) && !ft_ismeta((*data)->args[(*data)->current + 1]) && (*data)->args[(*data)->current + 1] != '$')
	{
		((*data)->current)++;
		while (ft_isprint((*data)->args[(*data)->current]) && !ft_ismeta((*data)->args[(*data)->current]) && (*data)->args[(*data)->current] != '$' && (*data)->args[(*data)->current] != '\0')
			((*data)->current)++;
		return (1);
	}
	return (0);
}

static int squote_checker_handler(t_data **data, int *quote_flag)
{
	(*quote_flag)++;
	((*data)->current)++;
	while ((*data)->args[(*data)->current] != '\'' && (*data)->args[(*data)->current] != '\0')
		((*data)->current)++;
	if ((*data)->args[(*data)->current] == '\'')
		(*quote_flag)++;
	if (ft_isprint((*data)->args[(*data)->current + 1]) && !ft_ismeta((*data)->args[(*data)->current + 1]) && (*data)->args[(*data)->current + 1] != '$')
	{
		((*data)->current)++;
		while (ft_isprint((*data)->args[(*data)->current]) && !ft_ismeta((*data)->args[(*data)->current]) && (*data)->args[(*data)->current] != '$' && (*data)->args[(*data)->current] != '\0')
			((*data)->current)++;
		return (1);
	}
	return (0);
}

static int ft_checker(t_data *data, int *quote_flag, t_tkn_data *token)
{
	if (!ft_isprint(data->args[data->current]) && !(*quote_flag % 2))
		return (1);
	else if (ft_ismeta(data->args[data->current]) && !(*quote_flag % 2))
		return (1);
	else if (data->args[data->current] == '$')
	{
		token->type = WORD_DOL;
		get_variable_len(data, data->current, &token->variable_len);
	}
	else if (data->args[data->current] == '\"')
	{
		if (dquote_checker_handler(&data, &token, quote_flag))
			return (1);
	}
	else if (data->args[data->current] == '\'')
	{
		if (squote_checker_handler(&data, quote_flag))
			return (1);
	}
	return (0);
}

// static int ft_checker(t_data *data, int *quote_flag, t_tkn_data *token)
// {
// 	if (!ft_isprint(data->args[data->current]) && !(*quote_flag % 2))
// 		return (1);
// 	else if (ft_ismeta(data->args[data->current]) && !(*quote_flag % 2))
// 		return (1);
// 	else if (data->args[data->current] == '$')
// 	{
// 		token->type = WORD_DOL;
// 		get_variable_len(data, data->current, &token->variable_len);
// 		//useless
// 		/*if (token->variable_len == 0 && data->args[data->current + 1] == '\"')
// 				token->variable_len++;*/
// 	}
// 	else if (data->args[data->current] == '\"')
// 	{
// 		(*quote_flag)++;
// 		(data->current)++;
// 		while (data->args[data->current] != '\"' && data->args[data->current] != '\0')
// 		{
// 			if (data->args[data->current] == '$')
// 				get_variable_len(data, data->current, &token->variable_len);
// 			(data->current)++;
// 		}
// 		if (data->args[data->current] == '\"')
// 			(*quote_flag)++;
// 		if (data->args[data->current] && ft_isprint(data->args[data->current + 1]) && !ft_ismeta(data->args[data->current + 1]) && data->args[data->current + 1] != '$')
// 		{
// 			(data->current)++;
// 			while (ft_isprint(data->args[data->current]) && !ft_ismeta(data->args[data->current]) && data->args[data->current] != '$' && data->args[data->current] != '\0')
// 				(data->current)++;
// 			return (1);
// 		}
// 	}
// 	else if (data->args[data->current] == '\'')
// 	{
// 		(*quote_flag)++;
// 		(data->current)++;
// 		while (data->args[data->current] != '\'' && data->args[data->current] != '\0')
// 			(data->current)++;
// 		if (data->args[data->current] == '\'')
// 			(*quote_flag)++;
// 		if (ft_isprint(data->args[data->current + 1]) && !ft_ismeta(data->args[data->current + 1]) && data->args[data->current + 1] != '$')
// 		{
// 			(data->current)++;
// 			while (ft_isprint(data->args[data->current]) && !ft_ismeta(data->args[data->current]) && data->args[data->current] != '$' && data->args[data->current] != '\0')
// 				(data->current)++;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

static void ft_assign_word_token(int *q_flag, t_tkn_data **token, char **string, t_types type)
{
	(*token)->type = type;
	(*token)->variable_len = 0;
	(*token)->cmd_exec_path = NULL;
	*q_flag = 0;
	*string = NULL;
}

static int qflag_word_token_handler(t_data **data, int *q_flag, t_tkn_data **token, t_list **node, char **string)
{
	if ((*q_flag) % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		((*data)->current)--;
		return (-1);
	}
	if (!((*q_flag) % 2) && *q_flag != 0)
		quote_removal_copy(*string, *data, *token, *node, *q_flag);
	else
	{
		*string = ft_substr((*data)->args, (*data)->start, (*data)->current - (*data)->start);
		copy_assign(*string, *data, *token, *node);
	}
	((*data)->current)--;
	return (0);
}

int ft_word_token(t_data *data, t_types type)
{
	t_list *node;
	char *string;
	t_tkn_data *token;
	int quote_flag;
	
	memory_allocator((void **)&node, sizeof(t_list), data);
	memory_allocator((void **)&token, sizeof(t_tkn_data), data);
	ft_assign_word_token(&quote_flag, &token, &string, type);
	while (data->args[data->current])
	{
		if (ft_checker(data, &quote_flag, token))
			break ;
		if (data->args[data->current])
			(data->current)++; 
	}
	if (qflag_word_token_handler(&data, &quote_flag, &token, &node, &string) == -1)
		return (-1);
	return (0);
}

// int ft_word_token(t_data *data, t_types type)
// {
// 	t_list *node;
// 	char *string;
// 	t_tkn_data *token;
// 	int quote_flag;
	
// 	memory_allocator((void **)&node, sizeof(t_list), data);
// 	memory_allocator((void **)&token, sizeof(t_tkn_data), data);
// 	quote_flag = 0;
// 	token->type = type;
// 	token->variable_len = 0;
// 	token->cmd_exec_path = NULL;
// 	string = NULL;
// 	while (data->args[data->current])
// 	{
// 		if (ft_checker(data, &quote_flag, token))
// 			break ;
// 		if (data->args[data->current])
// 			(data->current)++; 
// 	}
// 	if (quote_flag % 2 != 0)
// 	{
// 		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
// 		(data->current)--;
// 		return (-1);
// 	}
// 	if (!(quote_flag % 2) && quote_flag != 0)
// 		quote_removal_copy(string, data, token, node, quote_flag);
// 	else
// 	{
// 		string = ft_substr(data->args, data->start, data->current - data->start);
// 		copy_assign(string, data, token, node);;
// 	}
// 	(data->current)--;
// 	return (0);
// }