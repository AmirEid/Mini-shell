/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:41:39 by aeid              #+#    #+#             */
/*   Updated: 2024/07/09 11:36:26 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static int ft_get_list_size(t_list *list)
{
	int size;
	t_list *current;
	t_tkn_data *tokendata;

	size = 0;
	current = list;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == COMMAND || tokendata->type == WORD)
			size++;
		else
			break;
		current = current->next;
	}
	return (size);
}

static char **ft_get_commands(t_list *tokens, t_list **current)
{
	t_tkn_data *tokendata;
	char **args;
	int len;
	int i;

	i = -1;
	len = ft_get_list_size(tokens);
	memory_allocator((void **)&args, sizeof(char *) * (len + 1));
	args[len] = NULL;
	while (*current != NULL && ++i < len)
	{
		tokendata = (t_tkn_data *)(*current)->content;
		if (tokendata->type == COMMAND || tokendata->type == WORD)
			args[i] = ft_strdup(tokendata->token);
		(*current) = (*current)->next;
	}
	return (args);
}

static char **ft_get_env_matrix(t_list *env)
{
	t_list *current;
	char **envp;
	int len;
	int i;

	i = -1;
	current = env;
	len = ft_lstsize(env);
	memory_allocator((void **)&envp, sizeof(char *) * (len + 1));
	envp[len] = NULL;
	while (current != NULL && ++i < len)
	{
		envp[i] = ft_strdup((char *)current->content);
		current = current->next;
	}
}

void ft_command_execution(t_list *tokens, t_list *env, t_list **current)
{
	char **args;
	char **envp;
	//t_list *curr;
	
	args = ft_get_commands(tokens, *current);
	envp = ft_get_env_matrix(env);

	free_mtx(envp);
	free_mtx(args);
}