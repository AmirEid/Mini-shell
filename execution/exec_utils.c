/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:03:03 by aeid              #+#    #+#             */
/*   Updated: 2024/07/11 18:16:56 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void open_files_errors_manager(int fd, char *exit_message, int exit_status, char *file_name)
{
	if (fd < 0)
	{
		if (file_name)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file_name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(exit_message, 2);
		}
		else
			ft_putstr_fd(exit_message, 2);
		exit(exit_status);
	}
}

void ft_dup2_error_manager(int fd, char *exit_message, int exit_status)
{
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(exit_message, 2);
		close(fd);
		exit(exit_status);
	}
}