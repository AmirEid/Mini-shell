/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:53:58 by anomourn          #+#    #+#             */
/*   Updated: 2024/08/01 19:33:36 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	memory_allocator(void **ptr, size_t size, t_data *data)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		perror("malloc");
		free_all(data);
		exit(exit_status);
		return ;
	}
	// list_add_front_node(&g_data->garbage, *ptr);
}

int	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_ismeta(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	get_variable_len(t_data *data, int dol_position, int *variable_len)
{
	dol_position++;
	while (!ft_isquote(data->args[dol_position])
		&& !ft_ismeta(data->args[dol_position])
		&& (ft_isprint(data->args[dol_position]))
		&& (data->args[dol_position] != '\0')
		&& (data->args[dol_position] != '$'))
	{
		dol_position++;
		(*variable_len)++;
	}
}

