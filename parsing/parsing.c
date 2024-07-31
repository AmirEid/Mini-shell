/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:47 by aeid              #+#    #+#             */
/*   Updated: 2024/07/31 21:46:32 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

int ft_get_process_num(t_list *tokens)
{
	t_list *current;
	t_tkn_data *tokendata;
	int process_num;

	process_num = 0;
	current = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == META_PIPE)
			process_num++;
		current = current->next;
	}
	return (process_num + 1);
}

void ft_parsing(t_data *data, t_list *tokens)
{
	char **path;
	
	if (data->exit_code == -1)
		return ;
	path = get_cmd_path(data->mini_env, data);
	data->list_size = ft_lstsize(tokens);
	expander(tokens, data);
	//what is this?????????
	//execute_command(tokens, data);
	ft_parser(tokens, data);
	define_commands(tokens, path);
	data->process_num = ft_get_process_num(tokens);
	define_builtins(tokens);
	if (path)
		free_mtx(path);
}
