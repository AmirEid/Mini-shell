/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:53:42 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:15:43 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void	ft_redir_out(t_list *file, int *redi_num, t_data *data)
{
	t_tkn_data	*tokendata;
	int			p_errno;
	int			fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open (tokendata->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	//printf("fd: %d\n", fd);
	if (fd == -1)
	{
		p_errno = errno;
		open_files_errors_manager(fd, tokendata->token, p_errno);
		data->exit_code = -1;
		//exit(1);
		// exit_status = 1;
		return ;
	}
	if ((*redi_num) - 1 == 0)
	{
		dup2(fd, 1);
		if (fd == -1)
		{
			p_errno = errno;
			ft_dup2_error_manager(fd, p_errno);
			data->exit_code = -1;
			close(fd);
			//exit(1);
			// exit_status = 1;
			return ;
		}	
	}
	(*redi_num)--;
	close(fd);
}
