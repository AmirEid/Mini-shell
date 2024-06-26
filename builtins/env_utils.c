/* ************************************************************************** */
/*			                                                                  */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:58:38 by anomourn          #+#    #+#             */
/*   Updated: 2024/06/25 12:46:07 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void	set_env(char *name, char *value, t_list *env)
{
	t_list	*current;
	char	*new_entry;
	size_t	new_entry_len;

	current = env;
	new_entry_len = ft_strlen(name) + ft_strlen(value) + 2; // for '=' and null terminator
	new_entry = malloc(new_entry_len);
	if (new_entry == NULL)
	{
		perror("malloc");
		return;
	}
	strcpy(new_entry, name);
	new_entry[ft_strlen(name)] = '=';
	strcpy(new_entry + ft_strlen(name) + 1, value);
	while (current)
	{

		if (ft_strncmp(, name, ft_strlen(name)) == 0 && env[i][ft_strlen(name)] == '=')
		{
			free(env[i]);
			env[i] = new_entry;
			return;
		}
	}
	env[i] = new_entry;
	env[i + 1] = NULL;
}

char *ft_getenv(t_data *data, char *value)
{
	t_list	*current;
	char	*name;
	size_t	name_len;

	current = data->mini_env;
	name_len = ft_strlen(value);
	while (current)
	{
		name = ft_strchr(current->content, '=');
		if (name == NULL)
		{
			current = current->next;
			continue;
		}
		if (ft_strncmp(current->content, value, name_len) == 0 && current->content[name_len] == '=')
			return (name + 1);
		current = current->next;
	}
	return (NULL);
}

