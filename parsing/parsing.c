/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:47 by aeid              #+#    #+#             */
/*   Updated: 2024/07/30 14:44:39 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"


void ft_parsing(t_data *data, t_list *tokens)
{
	char **path;
	
	if (exit_status == -1)
		return ;
	path = get_cmd_path(data->mini_env, data);
	data->list_size = ft_lstsize(tokens);
	expander(tokens, data);
	//what is this?????????
	//execute_command(tokens, data);
	ft_parser(tokens, data);
	define_commands(tokens, path);
	define_builtins(tokens);
	if (path)
		free_mtx(path);
}
