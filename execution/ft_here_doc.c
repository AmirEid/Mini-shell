/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:17 by aeid              #+#    #+#             */
/*   Updated: 2024/07/12 00:33:18 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void ft_heredoc(t_list *file)
{
	t_tkn_data *tokendata;
	int p_errno;
	char *buffer;
	int fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		buffer = get_next_line(0);
		//handle this properly
		if (ft_strncmp(tokendata->token, buffer, ft_strlen(tokendata->token)) == 0 || buffer == NULL)
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	get_next_line(-1);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	dup2(fd, 0);
	if (fd == -1)
	{
		p_errno = errno;
		unlink(".heredoc");
		ft_dup2_error_manager(fd, p_errno);
	}
	unlink(".heredoc");
	close(fd);
}
