/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:51 by aeid              #+#    #+#             */
/*   Updated: 2024/07/12 00:29:10 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void ft_redir_in(t_list *file)
{
	t_tkn_data *tokendata;
	int p_errno;
	int fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open(tokendata->token, O_RDONLY);
	if (fd == -1)
	{
		p_errno = errno;
		open_files_errors_manager(fd, tokendata->token, p_errno);
	}
	dup2(fd, 0);
	if (fd == -1)
	{
		p_errno = errno;
		ft_dup2_error_manager(fd, p_errno);
	}
	close(fd);
}
