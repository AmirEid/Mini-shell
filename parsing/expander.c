/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:03:20 by aeid              #+#    #+#             */
/*   Updated: 2024/07/30 16:39:36 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static int dollar_counter(char *tkn_str)
{
	int i;
	int num_of_dollars;

	i = -1;
	num_of_dollars = 0;
	while (tkn_str[++i] != '\0')
	{
		if (tkn_str[i] == '$')
			num_of_dollars++;
	}
	return (num_of_dollars);
}

static void get_var_len(char *str, int *variable_len)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	(*variable_len) = i;
}


static char *meta_dol_expander(t_list *mini_env, int variable_len, char *tkn_str, t_data *data)
{
	int i;
	char *variable;
	char *after_expand;

	i = 0;
	variable = NULL;
	after_expand = NULL;
	// if (variable_len == 0 || tkn_str[i] == '\0' || tkn_str[i] == ' ')
	// 	return ("");
	memory_allocator((void **)&variable, variable_len + 1, data);
	while (i < variable_len)
	{
		variable[i] = tkn_str[i];
		i++;
	}
	variable[i] = '\0';
	after_expand = search_env(mini_env, variable, data);
	//free(*tkn_str);
	free(variable);
	if (after_expand)
		return (after_expand);
	data->exp_var = 1;
	return(NULL);
}

static void process_dollar_expansion(int variable_len, char **tkn_str, t_data *data, char *tmp, char **string)
{
    int i = 0;
    char num_of_dollars = dollar_counter(*tkn_str);

    while (num_of_dollars > 0)
    {
        get_var_len(tmp + i + 1, &variable_len);
        *tkn_str = meta_dol_expander(data->mini_env, variable_len, tmp + i + 1, data);
        num_of_dollars--;
        i += variable_len + 1;
        if (*tkn_str)
            *string = ft_strjoin(*string, *tkn_str);
    }
}

static void meta_dol_expander_manager(int variable_len, char **tkn_str, t_data *data, t_types type)
{
    char *string = NULL;
    char *tmp = ft_strdup(*tkn_str);

    if (variable_len == 0 || (*tkn_str)[1] == '\0' || (*tkn_str)[1] == ' ')
        return;

    process_dollar_expansion(variable_len, tkn_str, data, tmp, &string);

    if (*tkn_str)
    {
        free(*tkn_str);
        *tkn_str = NULL;
    }
    if ((type == META_HEREDOC || type == META_REDIR_IN || type == META_REDIR_OUT || type == META_APPEND) && data->exp_var)
    {
        *tkn_str = tmp;
        free(string);
    }
    else
    {
        *tkn_str = string;
        free(tmp);
    }
}

// static void meta_dol_expander_manager(int variable_len, char **tkn_str, t_data *data, t_types type)
// {
// 	char *string;
// 	int i;
// 	char num_of_dollars;
// 	char *tmp;

// 	i = 0;
// 	tmp = ft_strdup(*tkn_str);
// 	string = NULL;
// 	if (variable_len == 0 || (*tkn_str)[i + 1] == '\0' || (*tkn_str)[i + 1] == ' ')
// 		return ;
// 	num_of_dollars = dollar_counter(*tkn_str);
// 	while (num_of_dollars > 0)
// 	{
// 		get_var_len(tmp + i + 1, &variable_len);
// 		*tkn_str = meta_dol_expander(data->mini_env, variable_len, tmp + i + 1, data);
// 		num_of_dollars--;
// 		i += variable_len + 1;
// 		if (*tkn_str)
// 			string = ft_strjoin(string, *tkn_str);
// 	}
// 	if (*tkn_str)
// 	{
// 		free(*tkn_str);
// 		*tkn_str = NULL;
// 	}
// 	if ((type == META_HEREDOC || type == META_REDIR_IN || type == META_REDIR_OUT || type == META_APPEND) && data->exp_var)
// 	{
// 		*tkn_str = tmp;
// 		free(string);
// 	}
// 	else
// 	{
// 		*tkn_str = string;
// 		free(tmp);
// 	}
// }

// static void dquote_expander(t_list *mini_env, int variable_len, char **tkn_str, t_data *data)
// {
// 	int i;
// 	int start;
// 	char *variable;
// 	char *var_expand;
// 	char *new;

// 	i = 0;
// 	start = 0;
// 	variable = NULL;
// 	var_expand = NULL;
// 	new = NULL;
// 	if (variable_len == 0 || (*tkn_str)[i + 1] == '\0' || (*tkn_str)[i + 1] == ' ')
// 			return ;
// 	while ((*tkn_str)[i] != '\0')
// 	{
// 		if ((*tkn_str)[i] == '$' && (*tkn_str)[i + 1] != '\0' && (*tkn_str)[i + 1] != ' ')
// 		{
// 			i++;
// 			while (ft_isprint((*tkn_str)[i]) && (*tkn_str)[i] != '\0' && !ft_ismeta((*tkn_str)[i]) && variable_len > 0 && (*tkn_str)[i] != '$')
// 			{
// 				i++;
// 				variable_len--;
// 			}
// 			memory_allocator((void **)&variable, i - start, data);
// 			ft_strlcpy(variable, &(*tkn_str)[start + 1], i - start);
// 			var_expand = search_env(mini_env, variable, data);
// 			if (var_expand)
// 				new = ft_strjoin(new, var_expand);
// 			else if ((*tkn_str)[i] != '\0')
// 				new = ft_strjoin(new,"");
// 			free(variable);
// 			if (var_expand)
// 				free(var_expand);
// 		}
// 		else if ((*tkn_str)[i] == '$')
// 		{
// 			new = ft_strjoin(new, "$");
// 			i++;
// 		}
// 		else
// 		{
// 			while ((*tkn_str)[i] != '\0' && !ft_ismeta((*tkn_str)[i]) && (*tkn_str)[i] != '$')	
// 				i++;
// 			new = ft_strjoin(new, ft_substr(*tkn_str, start, i - start));
// 		}
// 		start = i;
// 	}
// 	free(*tkn_str);
// 	*tkn_str = new;
// }
static void expand_variable(t_list *mini_env, int *variable_len, char **tkn_str, t_data *data, int *i, int *start, char **new)
{
    char *variable = NULL;
    char *var_expand = NULL;

    (*i)++;
    while (ft_isprint((*tkn_str)[*i]) && (*tkn_str)[*i] != '\0' && !ft_ismeta((*tkn_str)[*i]) && *variable_len > 0 && (*tkn_str)[*i] != '$')
    {
        (*i)++;
        (*variable_len)--;
    }
    memory_allocator((void **)&variable, *i - *start, data);
    ft_strlcpy(variable, &(*tkn_str)[*start + 1], *i - *start);
    var_expand = search_env(mini_env, variable, data);
    if (var_expand)
        *new = ft_strjoin(*new, var_expand);
    else if ((*tkn_str)[*i] != '\0')
        *new = ft_strjoin(*new, "");
    free(variable);
    if (var_expand)
        free(var_expand);
}

static void append_non_dollar_characters(char **tkn_str, int *i, int *start, char **new)
{
    while ((*tkn_str)[*i] != '\0' && !ft_ismeta((*tkn_str)[*i]) && (*tkn_str)[*i] != '$')
        (*i)++;
    *new = ft_strjoin(*new, ft_substr(*tkn_str, *start, *i - *start));
}

static void dquote_expander(t_list *mini_env, int variable_len, char **tkn_str, t_data *data)
{
    int i = 0;
    int start = 0;
    char *new = NULL;

    if (variable_len == 0 || (*tkn_str)[i + 1] == '\0' || (*tkn_str)[i + 1] == ' ')
        return;
    while ((*tkn_str)[i] != '\0')
    {
        if ((*tkn_str)[i] == '$' && (*tkn_str)[i + 1] != '\0' && (*tkn_str)[i + 1] != ' ')
        {
            expand_variable(mini_env, &variable_len, tkn_str, data, &i, &start, &new);
        }
        else if ((*tkn_str)[i] == '$')
        {
            new = ft_strjoin(new, "$");
            i++;
        }
        else
        {
            append_non_dollar_characters(tkn_str, &i, &start, &new);
        }
        start = i;
    }
    free(*tkn_str);
    *tkn_str = new;
}
static void type_checker(t_types *cur_type, t_types *prev_type, t_data *data, t_tkn_data *current)
{	
	if (*cur_type == META_DOL)
		meta_dol_expander_manager(current->variable_len, &current->token, data, *prev_type);
	else if (*cur_type == SPECIAL_DQUOTE || *cur_type == WORD_DOL || *cur_type == WORD_WITH_DQUOTE_INSIDE)
	{
		dquote_expander(data->mini_env, current->variable_len, &current->token, data);
		if (*prev_type != META_HEREDOC)
			current->type = WORD;
	}
	else if ((*cur_type == SPECIAL_SQUOTE || *cur_type == WORD_WITH_SQUOTE_INSIDE) && *prev_type != META_HEREDOC)
		current->type = WORD;
}

void expander(t_list *tokens, t_data *data)
{
	t_list *current;
	t_tkn_data *tmp;
	t_list *prev;
	t_tkn_data *prev_tmp;

	current = tokens;
	prev = current;
	prev_tmp = NULL;
	tmp = NULL;
	while (current)
	{
		tmp = (t_tkn_data *)current->content;
		prev_tmp = (t_tkn_data *)prev->content;
		type_checker(&tmp->type, &prev_tmp->type, data, tmp);
		prev = current;
		current = current->next;
	}
}
