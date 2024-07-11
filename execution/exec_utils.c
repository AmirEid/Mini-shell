/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:03:03 by aeid              #+#    #+#             */
/*   Updated: 2024/07/11 17:04:05 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void open_files_errors_manager(int fd, char *exit_message, int exit_status)
{
	if (fd < 0)
	{
		ft_putstr_fd(exit_message, 2);
		exit(exit_status);
	}
}
