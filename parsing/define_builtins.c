/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:44:06 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:28:14 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	iteration_check(char *str, t_types *type)
{
	if (!ft_strncmp(str, "export", 7))
		*type = WORD_EXPORT;
	else if (!ft_strncmp(str, "unset", 6))
		*type = WORD_UNSET;
	else if (!ft_strncmp(str, "env", 4))
		*type = WORD_ENV;
	else if (!ft_strncmp(str, "echo", 5))
		*type = WORD_ECHO;
	else if ((!ft_strncmp(str, "cd", 3)))
		*type = WORD_CD;
	else if (!ft_strncmp(str, "exit", 5))
		*type = WORD_EXIT;
	else if ((!ft_strncmp(str, "pwd", 4)))
		*type = WORD_PWD;
	else if (!ft_strncmp(str, "/", 1))
		*type = COMMAND;
}

void	define_builtins(t_list *token)
{
	char		*tkn_str;
	t_list		*current;
	t_list		*prev;
	t_tkn_data	*prev_tmp;

	current = token;
	prev = current;
	prev_tmp = NULL;
	while (current != NULL)
	{
		prev_tmp = (t_tkn_data *)(prev->content);
		if (prev_tmp->type != META_HEREDOC)
		{
			tkn_str = ((t_tkn_data *)(current->content))->token;
			iteration_check(tkn_str, &((t_tkn_data *)(current->content))->type);
		}
		prev = current;
		current = current->next;
	}
}
