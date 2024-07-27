/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:41:39 by aeid              #+#    #+#             */
/*   Updated: 2024/07/27 17:53:51 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	ft_get_list_size(t_list *list)
{
	int			size;
	t_list		*current;
	t_tkn_data	*tokendata;

	size = 0;
	current = list;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == COMMAND || tokendata->type == WORD)
			size++;
		else
			break ;
		current = current->next;
	}
	return (size);
}

static char	**ft_get_commands(t_list *tokens, t_list *current, t_data *data)
{
	t_tkn_data	*tokendata;
	char		**args;
	int			len;
	int			i;
	t_list		*temp;

	i = -1;
	temp = current;
	len = ft_get_list_size(tokens);
	memory_allocator((void **)&args, sizeof(char *) * (len + 1), data);
	args[len] = NULL;
	while (temp != NULL && ++i < len)
	{
		tokendata = (t_tkn_data *)temp->content;
		//double check this
		if (tokendata->type != META_PIPE && tokendata->type != META_REDIR_IN
			&& tokendata->type != META_REDIR_OUT
			&& tokendata->type != META_APPEND
			&& tokendata->type != META_HEREDOC)
			args[i] = (tokendata->token);
		temp = temp->next;
	}
	return (args);
}

static char	**ft_get_env_matrix(t_list *env, t_data *data)
{
	t_list	*current;
	char	**envp;
	int		len;
	int		i;

	i = -1;
	current = env;
	len = ft_lstsize(env);
	memory_allocator((void **)&envp, sizeof(char *) * (len + 1), data);
	envp[len] = NULL;
	while (current != NULL && ++i < len)
	{
		envp[i] = ((char *)current->content);
		current = current->next;
	}
	return (envp);
}

void print_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i] != NULL)
		printf("%s\n", matrix[i]);
}

void	ft_command_execution(t_list *tokens, t_list *env, t_list *current, t_data *data)
{
	char		**args;
	char		**envp;
	t_tkn_data	*tokendata;

	tokendata = (t_tkn_data *)current->content;
	args = ft_get_commands(tokens, current, data);
	envp = ft_get_env_matrix(env, data);
	//print_matrix(args);
	execve(tokendata->cmd_exec_path, args, envp);
	//exit(0);
	//print_matrix(envp);
	free_null(envp);
	free_null(args);
}
