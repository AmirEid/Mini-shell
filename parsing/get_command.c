/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:08:41 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:36:30 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static char	*get_command(char **paths, char *cmd)
{
	char	*p;
	char	*command;

	if (!paths)
		return (NULL);
	while (*paths)
	{
		p = ft_strjoin(*paths, "/");
		command = ft_strjoin(p, cmd);
		free(p);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	**get_cmd_path(t_list *mini_env, t_data *data)
{
	char	*path_str;
	char	**path;

	path_str = search_env(mini_env, "PATH", data);
	if (path_str == NULL)
		return (NULL);
	path = ft_split(path_str, ':');
	free(path_str);
	return (path);
}


void	define_commands(t_list *tokens, char **path)
{
	t_list		*current;
	t_tkn_data	*string;

	current = tokens;
	string = NULL;
	while (current)
	{
		string = (t_tkn_data *)current->content;
		if (string->type == WORD)
			string->cmd_exec_path = get_command(path, string->token);
		if (!string->cmd_exec_path && !ft_strncmp(string->token, "/", 1))
			string->cmd_exec_path = ft_strdup(string->token);
		if (string->cmd_exec_path != NULL)
			string->type = COMMAND;
		current = current->next;
	}
}
