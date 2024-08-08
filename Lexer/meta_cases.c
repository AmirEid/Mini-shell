/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:13:57 by aeid              #+#    #+#             */
/*   Updated: 2024/08/08 17:33:44 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"
/*
void redi_out_parser(t_data *data, t_list *node, t_tkn_data *token)
{
	int counter;

	counter = 0;
	while (data->args[data->current] == '>')
		(data->current)++;
	if (counter > 2 || data->args[data->current] == '<')
	{
		if (data->args[data->current] == '<')
			ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		
	}
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		exit_status = 2;
	}
	else if (data->args[data->current] == '<')
	
}*/

void	redirect_meta(t_data *data, t_list *node, t_tkn_data *token)
{
	if (data->args[data->current] == '>')
	{
		(data->current)++;
		if (data->args[data->current] == '>')
			(data->current)++;	
	}
	else if (data->args[data->current] == '<')
	{
		(data->current)++;
		if (data->args[data->current] == '<')
			(data->current)++;
	}
	else 
		(data->current)++;
	token->token = ft_substr(data->args, data->start, data->current - data->start);
	node->content = token;
	node->next = NULL;
	ft_lstadd_back(&data->tokens, node);
}

// void redirect_meta(t_data *data, t_list *node, t_tkn_data *token)
// {
// 	if (data->args[data->current] == '>')
// 	{
// 		(data->current)++;
// 		if (data->args[data->current] == '>')
// 			(data->current)++;	
// 	}
// 	else if (data->args[data->current] == '<')
// 	{
// 		(data->current)++;
// 		if (data->args[data->current] == '<')
// 			(data->current)++;
// 	}
// 	else 
// 		(data->current)++;
// 	token->token = ft_substr(data->args, data->start, data->current - data->start);
// 	node->content = token;
// 	node->next = NULL;
// 	ft_lstadd_back(&data->tokens, node);
// }

void	pipe_meta(t_data *data, t_list *node, t_tkn_data *token)
{
	(data->current)++;
	token->token = ft_substr(data->args, data->start, data->current - data->start);
	node->content = token;
	node->next = NULL;
	ft_lstadd_back(&data->tokens, node);
}

//$ sign can be followed by alpha and _
// number 0 to 9
// ? sign
// else take only $ sign

static int	handle_dollar_meta(t_data **data, t_tkn_data **token)
{
	(*data)->current++;
	if (ft_isdigit((*data)->args[(*data)->current]))
		return (1);
	(*data)->current--;
	get_variable_len(*data, (*data)->current, &(*token)->variable_len);
	(*data)->current++;
	return (0);
}

static void	ft_quote_handler_meta(t_data **data, t_tkn_data **token)
{
	int	tmp;

	tmp = (*data)->args[(*data)->current];
	(*data)->current++;
	if ((*data)->args[(*data)->current] == '$')
	{
		if (tmp == 39)
			(*token)->variable_len = (*token)->variable_len;
		else
			get_variable_len(*data, (*data)->current, &(*token)->variable_len);
	}
	(*data)->start = (*data)->current;
	while ((*data)->args[(*data)->current] && (*data)->args[(*data)->current] != tmp)
		(*data)->current++;
	if ((*token)->variable_len > 0)
		(*token)->type = META_DOL;
	else
		(*token)->type = WORD;
}

static char	*dollar_m(t_data *data, t_tkn_data *token)
{
	if (data->args[data->current] == '$')
	{
		if (handle_dollar_meta(&data, &token))
			return (NULL);	
	}
	if (ft_isquote(data->args[data->current]))
		ft_quote_handler_meta(&data, &token);
	else if (ft_isalpha(data->args[data->current]))
		while (ft_isprint(data->args[data->current]))
		{
			(data->current)++;
			if (ft_ismeta(data->args[data->current]) || ft_isquote(data->args[data->current]))
				break ;
		}
	else if (ft_isdigit(data->args[data->current]) || data->args[data->current] == '?')
	{
		if (data->args[data->current] == '?')
			token->type = META_STATUS;
		(data->current)++;
	}
	return(ft_substr(data->args, data->start, data->current - data->start));
}

static void ft_add_to_token(t_data **data, t_tkn_data **token)
{
	char *tmp;
	//char *to_free;
	
	tmp = dollar_m(*data, *token);
	//to_free = (*token)->token;
	(*token)->token = ft_join((*token)->token, tmp);
	free(tmp);
	(*data)->current++;
}

// static void ft_add_to_token(t_data **data, t_tkn_data **token)
// {
// 	int flag;
// 	int counter;
// 	int current;
// 	int start;
// 	char *tmp;

// 	flag = 1;
// 	counter = 0;
// 	current = (*data)->current;
// 	start = ++counter;
// 	while(ft_isprint((*data)->args[current]) && (*data)->args[current] != '\0')
// 	{
// 		current++;
// 		if (ft_isquote((*data)->args[current]))
// 			flag++;
// 	}
// 	if ((*data)->args[current] == '\0' && flag % 2 != 0)
// 	{
// 		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
// 		(*data)->exit_code = -1;
// 		exit_status = 1;
// 	}
// 	memory_allocator((void **)&tmp, current - start + 1, *data);
// }


void	dollar_meta(t_data *data, t_list *node, t_tkn_data *token)
{
	if (data->args[data->current] == '$')
	{
		if (handle_dollar_meta(&data, &token))
			return ;	
	}
	if (ft_isquote(data->args[data->current]))
		ft_quote_handler_meta(&data, &token);
	else if (ft_isalpha(data->args[data->current]))
		while (ft_isprint(data->args[data->current]))
		{
			(data->current)++;
			if (ft_ismeta(data->args[data->current]) || ft_isquote(data->args[data->current]))
				break ;
		}
	else if (ft_isdigit(data->args[data->current]) || data->args[data->current] == '?')
	{
		if (data->args[data->current] == '?')
			token->type = META_STATUS;
		(data->current)++;
	}
	token->token = ft_substr(data->args, data->start, data->current - data->start);
	if (data->args[data->current] == '\"' || data->args[data->current] == '\'')
		ft_add_to_token(&data, &token);
	node->content = token;
	node->next = NULL;
	ft_lstadd_back(&data->tokens, node);
}

// void dollar_meta(t_data *data, t_list *node, t_tkn_data *token)
// {
// 	int tmp;
	
// 	tmp = 0;
// 	if (data->args[data->current] == '$')
// 	{
// 		(data->current)++;
// 		if (ft_isdigit(data->args[data->current]))
// 			return ;
// 		(data->current)--;
// 	}
// 	get_variable_len(data, data->current, &token->variable_len);
// 	(data->current)++;
// 	if (ft_isquote(data->args[data->current]))
// 	{
// 		tmp = data->args[data->current];
// 		(data->current)++;
// 		if (data->args[data->current] == '$')
// 			get_variable_len(data, data->current, &token->variable_len);
// 		data->start = data->current;
// 		while (data->args[data->current] != tmp)
// 			(data->current)++;
// 		token->type = WORD;
// 	}
// 	else if (ft_isalpha(data->args[data->current]))
// 		while ((ft_isalpha(data->args[data->current]) || data->args[data->current] == '_') || data->args[data->current] == '?' || data->args[data->current] == '$')
// 			(data->current)++;
// 	else if (ft_isdigit(data->args[data->current]) || data->args[data->current] == '?')
// 	{
// 		if (data->args[data->current] == '?')
// 			token->type = META_STATUS;
// 		(data->current)++;
// 	}
// 	token->token = ft_substr(data->args, data->start, data->current - data->start);
// 	if (data->args[data->current] == '\"' || data->args[data->current] == '\'')
// 		(data->current)++;
// 	node->content = token;
// 	node->next = NULL;
// 	ft_lstadd_back(&data->tokens, node);
// }
