/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:25:53 by aeid              #+#    #+#             */
/*   Updated: 2024/07/29 18:13:30 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_data	initialize_data()
{
	t_data	data;
		
	data.mini_env = NULL;
	data.tokens = NULL;
	data.list_size = 0;
	//ata.exit_status = 0;
	data.current = 0;
	data.start = 0;
	//data.exit_code = 0;
	data.pwd = NULL;
	data.old_pwd = NULL;
	data.args = NULL;
	data.env = NULL;
	data.tmp_fd = 0;

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
			break;
	}
}

void	reinitialize_data(t_data *data)
{
	exit_status = 0;
	data->current = 0;
	data->start = 0;
	data->list_size = 0;
	data->tokens = NULL;
	data->args = NULL;
	data->env = NULL;
	data->pwd = NULL;
	data->tmp_fd = 0;
}
