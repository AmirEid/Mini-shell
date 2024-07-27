/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:15:35 by anomourn          #+#    #+#             */
/*   Updated: 2024/07/27 14:56:49 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void	free_list(t_list *list)
{
	t_list	*tmp;
	t_tkn_data	*tkn_data;
	
	tmp = NULL;
	tkn_data = NULL;
	while (list)
	{
		tmp = list;
		tkn_data = (t_tkn_data *)tmp->content;
		list = list->next;
		free(tkn_data->token);
		if (tkn_data->cmd_exec_path)
			free(tkn_data->cmd_exec_path);
		free(tkn_data);
		free(tmp);
	}
}

void    free_env_list(t_list **env_list) // for get_env
{
    t_list *tmp;
    t_list *next;

    tmp = *env_list;
    while (tmp != NULL)
    {
        next = tmp->next;
        free(tmp->content);
        free(tmp);
        tmp = next;
    }
    *env_list = NULL;
}

void free_all(t_data *data)
{
	int	i;

	i = 0;
	//free_env_list(&data->mini_env);
	free_list(data->tokens);
	//free(data->pwd);
	//free(data->old_pwd);
	free(data->args);
	if (data->env)
	// {
	// 	while (data->env[i] != NULL)
	// 	{
	// 		free(data->env[i]);
	// 		i++;
	// 	}
	// 	free(data->env);
	// }
	free(data);
}