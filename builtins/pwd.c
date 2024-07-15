/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:27:06 by anomourn          #+#    #+#             */
/*   Updated: 2024/07/15 16:59:05 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* Displays the current working directory */
int	ft_pwd(t_data *data)
{
	char	*str;

	str = malloc(sizeof(char) * PATH_MAX);
	if (str == NULL)
		return (1);
	if (getcwd(str, PATH_MAX) != NULL)
	{
		free(data->pwd);
		data->pwd = strdup(str);
		printf("%s\n", data->pwd);
	}
	else
	{
		free(str);
		return (2);
	}
	free(str);
	return (0);
}