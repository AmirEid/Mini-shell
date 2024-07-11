/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:51 by aeid              #+#    #+#             */
/*   Updated: 2024/07/11 18:19:02 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void ft_redir_in(t_list *file)
{
	t_tkn_data *tokendata;
	int fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open(tokendata->token, O_RDONLY);
	open_files_errors_manager(fd, "Permission denied", 1, tokendata->token);
	dup2(fd, 0);
	ft_dup2_error_manager(fd, "Error redirecting stdin", 1);
	close(fd);
}