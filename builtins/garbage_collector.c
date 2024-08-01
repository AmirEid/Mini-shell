/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:36:03 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/27 17:51:00 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	free_null(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_mtx(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free_null(path[i]);
		i++;
	}
	free_null(path);
}
