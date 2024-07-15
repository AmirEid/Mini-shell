/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:47 by aeid              #+#    #+#             */
/*   Updated: 2024/07/15 17:30:05 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"


void ft_parsing(t_data *data, t_list *tokens)
{
	char **path;
	
	path = get_cmd_path(data->mini_env);
	data->list_size = ft_lstsize(tokens);
	expander(data->mini_env, tokens);
	define_builtins(tokens);
	define_commands(tokens, path);
	execute_command(tokens, data);
	ft_parser(tokens);
	free_mtx(path);
}
