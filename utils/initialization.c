/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:25:53 by aeid              #+#    #+#             */
/*   Updated: 2024/08/08 19:01:48 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_data	initialize_data()
{
	t_data	data;

	data.mini_env = NULL;
	data.tokens = NULL;
	data.buffer_heredoc = NULL;
	data.list_size = 0;
	data.exp_var = 0;
	data.process_num = 0;
	data.current = 0;
	data.start = 0;
	data.exit_code = 0;
	data.pwd = NULL;
	data.old_pwd = NULL;
	data.args = NULL;
	data.env = NULL;
	data.tmp_fd = dup(0);
	data.tmp_fd2 = dup(1);
	return (data);
}

int	check_if_empty(char *args)
{
	size_t	i;

	i = 0;
		if (!args || !args[0])
			return (0);
		while (!ft_isprint(args[i]) && args[i] != '\0')
			i++;
		if (args[i] == '\0')
			return (0);
		return (1);
}

void	prompt_loop(t_data *data)
{
	//char	*str;
	while (1)
	{
		(*data).args = readline("minishell $ ");
		if ((*data).args == NULL)
			ft_sig_term(data);
		//add_history(str);
		if (!check_if_empty((*data).args))
		{
			free((*data).args);
			(*data).args = NULL;
		}
		else
			break ;
	}
}

void	reinitialize_data(t_data *data)
{
	data->exit_code = 0;
	data->old_pwd = NULL;
	data->current = 0;
	data->process_num = 0;
	data->exp_var = 0;
	data->start = 0;
	data->list_size = 0;
	data->buffer_heredoc = NULL;
	data->tokens = NULL;
	data->args = NULL;
	data->env = NULL;
	data->pwd = NULL;
	//exit_status = 0;
	// close(data->tmp_fd);
	// close(data->tmp_fd2);
	dup2(data->tmp_fd, 0);
	// //close(data->tmp_fd);
	dup2(data->tmp_fd2, 1);
	// close(data->tmp_fd2);
	// close(data->tmp_fd);
	//close(data->tmp_fd2);
}
