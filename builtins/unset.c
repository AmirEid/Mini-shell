/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:57:21 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/05 11:08:51 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	check_arg_of_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		error_export_unset('u', str);
		return (0);
	}
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			error_export_unset('u', str);
			return (0);
		}
	}
	return (1);
}

static void	unset_if_found(t_data data, char *str)
{
	t_list	**temp_env;
    t_list	*temp_node;
	char	*l_eq;
	int		flag;

	flag = 0;
	temp_env = &data.mini_env;
	while (*temp_env)
	{
		l_eq = ft_strdup((char *)((*temp_env)->content));
		if ((*temp_env)->print == 0 && !ft_strncmp(str, l_eq, biggest_strlen(str, l_eq)))
			flag++;
		if (ft_strchr(l_eq, '='))
			l_eq[ft_strchr(l_eq, '=') - l_eq] = '\0'; // il '=' diventa '\0'
		if (!ft_strncmp(str, l_eq, biggest_strlen(str, l_eq)))
			flag++;
		free(l_eq);
		if (flag)
		{
			temp_node = *temp_env;
			*temp_env = temp_node->next;
			free_null(temp_node->content);
			free_null(temp_node);
			return ;
		}
		temp_env = &(*temp_env)->next;
	}
}

// EXAMPLE :   unset a b c
// will unset a b c if founded and return a pointer to
// the next token after the last unsetted token
// in the case of the exampe above it will return a pointer to NULL
// if nothing is after the last element to unset
void 	ft_unset(t_data data, t_list *cur_token)
{
	char	*str;
	t_list	*curr;
	//t_list	*prev;

	//prev = cur_token;
	curr = cur_token->next;
	while (curr && till(((t_tkn_data *)(curr->content))->type))
	{
		str = ((t_tkn_data *)(curr->content))->token;
		if (check_arg_of_unset(str))
			unset_if_found(data, str);
		//prev = actual_node;
		curr = curr->next;
	}
}
