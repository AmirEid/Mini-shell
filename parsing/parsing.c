/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:57:47 by aeid              #+#    #+#             */
/*   Updated: 2024/08/08 19:59:40 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

int	ft_get_process_num(t_list *tokens)
{
	t_list		*current;
	t_tkn_data	*tokendata;
	int			process_num;

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

static bool head_checker(t_list *tokens)
{
	t_list *current;
	t_tkn_data *string;
	
	current = tokens;
	string = (t_tkn_data *)current->content;
	if (string->type == META_REDIR_IN || string->type == META_REDIR_OUT || string->type == META_APPEND || string->type == META_HEREDOC)
		return (true);
	return (false);
}

void	ft_parsing(t_data *data)
{
	char	**path;

	if (data->exit_code == -1)
		return ;
	path = get_cmd_path(data->mini_env, data);
	data->list_size = ft_lstsize(data->tokens);
	expander(data->tokens, data);
	ft_parser(data->tokens, data);
	if (data->exit_code == -1)
		return ;
	if (head_checker(data->tokens))
		ft_organizer1(&data->tokens);
	ft_organizer(data->tokens);
	define_commands(data->tokens, path);
	data->process_num = ft_get_process_num(data->tokens);
	define_builtins(data->tokens);
	if (path)
		free_mtx(path);
}
