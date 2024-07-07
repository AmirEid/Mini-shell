/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:47 by aeid              #+#    #+#             */
/*   Updated: 2024/07/05 20:29:16 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static void ft_free_path(char **path)
{
	int i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
}

void ft_parsing(t_data *data, t_list *tokens)
{
	char **path;
	
	path = get_cmd_path(data->mini_env);
	data->list_size = ft_lstsize(tokens);
	expander(data->mini_env, tokens);
	define_builtins(tokens);
	define_commands(tokens, path);
	ft_parser(data, tokens);
	ft_free_path(path);
}
