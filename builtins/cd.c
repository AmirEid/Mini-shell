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

char	*get_cd_path(t_list *tokens)
{
	char	*home;

	if (tokens->next == NULL || (strlen(((t_tkn_data *)tokens->next->content)->token) == 0))
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home);
	}
	return (((t_tkn_data *)tokens->next->content)->token);
}

int	update_old_pwd(t_data *data)
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

int	change_directory(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd error");
		return (-1);
	}
	return (0);
}

int	update_pwd(t_data *data)
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

int	ft_cd(t_list *tokens, t_data *data)
{
	char	*path;
    int		arg_count;
    t_list	*temp;
	
	arg_count = 0;
	temp = tokens;
	while (temp != NULL)
	{
		arg_count++;
		temp = temp->next;
	}
	if (arg_count > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (-1);
	}
	path = get_cd_path(tokens);
	if (path == NULL)
		return (-1);
	if (update_old_pwd(data) == -1)
		return (-1);
	if (change_directory(path) == -1)
		return (-1);
	if (update_pwd(data) == -1)
		return (-1);
	return (0);
}
