/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:44:06 by aeid              #+#    #+#             */
/*   Updated: 2024/07/22 21:25:20 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void define_builtins(t_list *token)
{
	char		*tkn_str;
	t_list		*current;
	t_list *prev;
	t_tkn_data *prev_tmp;
	
	current = token;
	prev = current;
	prev_tmp = NULL;
	while (current != NULL)
	{
		prev_tmp = (t_tkn_data *)(prev->content);
		if (prev_tmp->type != META_HEREDOC)
		{
			tkn_str = ((t_tkn_data *)(current->content))->token;
			if (!ft_strncmp(tkn_str, "export", 7))
				((t_tkn_data *)(current->content))->type = WORD_EXPORT;
			else if (!ft_strncmp(tkn_str, "unset", 6))
				((t_tkn_data *)(current->content))->type = WORD_UNSET;
			else if (!ft_strncmp(tkn_str, "env", 4))
				((t_tkn_data *)(current->content))->type = WORD_ENV;
			else if (!ft_strncmp(tkn_str, "echo", 5))
				((t_tkn_data *)(current->content))->type = WORD_ECHO;
			else if ((!ft_strncmp(tkn_str, "cd", 3)))
				((t_tkn_data *)(current->content))->type = WORD_CD;
			else if (!ft_strncmp(tkn_str, "exit", 5))
				((t_tkn_data *)(current->content))->type = WORD_EXIT;
			else if ((!ft_strncmp(tkn_str, "pwd", 4)))
				((t_tkn_data *)(current->content))->type = WORD_PWD;
		}
		prev = current;
		current = current->next;
	}
}
//what is this?????????
void	execute_command(t_list *tokens, t_data *data)
{
	t_list *current = tokens;
	
	while (current != NULL) {
		t_tkn_data *tkn_data = (t_tkn_data *)(current->content);
		if (tkn_data->type == WORD_CD)
			ft_cd(current, data);
		//else if (tkn_data->type == WORD_EXPORT)
		//
		//else if (tkn_data->type == WORD_UNSET)
		//
		//else if (tkn_data->type == WORD_ENV)
		//
		//else if (tkn_data->type == WORD_ECHO)
		//
		//else if (tkn_data->type == WORD_EXIT)
		//
		else if (tkn_data->type == WORD_PWD)
			ft_pwd(data);
		current = current->next;
	}
}
