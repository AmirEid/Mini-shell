/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:33:25 by anoukmourna       #+#    #+#             */
/*   Updated: 2024/06/24 19:16:52 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_cd_path(t_list *tokens, t_data *data, t_list *mini_env)
{
	char	*home;

	if (tokens->next == NULL
		|| (strlen(((t_tkn_data *)tokens->next->content)->token) == 0))
	{
		home = search_env(mini_env, "HOME", data);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_exit_status = 1;
			return (NULL);
		}
		return (home);
	}
	return (((t_tkn_data *)tokens->next->content)->token);
}

int	old_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (-1);
	}
	free(data->old_pwd);
	data->old_pwd = ft_strdup(cwd);
	if (data->old_pwd == NULL)
	{
		perror("strdup error");
		return (-1);
	}
	return (0);
}

int	change_direct(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd error");
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

int	up_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		return (-1);
	}
	free(data->pwd);
	data->pwd = ft_strdup(cwd);
	if (data->pwd == NULL)
	{
		perror("strdup error");
		return (-1);
	}
	return (0);
}

int	ft_cd(t_list *tokens, t_data *data, t_list *mini_env)
{
	char		*path;
	t_list		*temp;
	t_tkn_data	*token_data;

	if (data->list_size > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (-1);
	}
	temp = tokens;
	while (temp)
	{
		token_data = (t_tkn_data *)temp->content;
		if (!is_redirection(token_data, 1))
			break ;
		temp = temp->next;
	}
	path = get_cd_path(tokens, data, mini_env);
	if (path == NULL || old_pwd(data) == -1
		|| change_direct(path) == -1 || up_pwd(data) == -1)
		return (-1);
	g_exit_status = 0;
	return (0);
}
