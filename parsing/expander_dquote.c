/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:30:24 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 00:35:59 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	expand_variable(t_list *mini_env, int *variable_len, char **tkn_str,
		t_data *data, int *i, int *start, char **new)
{
	char	*variable;
	char	*var_expand;

	variable = NULL;
	var_expand = NULL;
	(*i)++;
	while (ft_isprint((*tkn_str)[*i]) && (*tkn_str)[*i] != '\0'
		&& !ft_ismeta((*tkn_str)[*i]) && *variable_len > 0
		&& (*tkn_str)[*i] != '$')
	{
		(*i)++;
		(*variable_len)--;
	}
	memory_allocator((void **)&variable, *i - *start, data);
	ft_strlcpy(variable, &(*tkn_str)[*start + 1], *i - *start);
	var_expand = search_env(mini_env, variable, data);
	if (var_expand)
		*new = ft_join(*new, var_expand);
	else if ((*tkn_str)[*i] != '\0')
		*new = ft_join(*new, "");
	free(variable);
	if (var_expand)
		free(var_expand);
}

static void	append_non_dollar_characters(char **tkn_str, int *i, int *start,
		char **new)
{
	char	*tmp;

	tmp = NULL;
	while ((*tkn_str)[*i] != '\0' && !ft_ismeta((*tkn_str)[*i])
		&& (*tkn_str)[*i] != '$')
		(*i)++;
	tmp = ft_substr(*tkn_str, *start, *i - *start);
	*new = ft_join(*new, tmp);
	free(tmp);
}

static int initialize_dquote_expander(int *i, int *start, char **new, int variable_len, char **tkn_str)
{
    *i = 0;
    *start = 0;
    *new = NULL;
    if (variable_len == 0 || (*tkn_str)[*i + 1] == '\0' || (*tkn_str)[*i + 1] == ' ')
        return 0;
    return 1;
}

void	dquote_expander(t_list *mini_env, int variable_len, char **tkn_str, t_data *data)
{
	int		i;
	int		start;
	char	*new;

	if (!initialize_dquote_expander(&i, &start, &new, variable_len, tkn_str))
		return ;
	while ((*tkn_str)[i] != '\0')
	{
		if ((*tkn_str)[i] == '$' && (*tkn_str)[i + 1] != '\0' && (*tkn_str)[i
			+ 1] != ' ')
		{
			expand_variable(mini_env, &variable_len, tkn_str, data, &i, &start,
					&new);
		}
		else if ((*tkn_str)[i] == '$')
		{
			new = ft_join(new, "$");
			i++;
		}
		else
			append_non_dollar_characters(tkn_str, &i, &start, &new);
		start = i;
	}
	free(*tkn_str);
	*tkn_str = new;
}
