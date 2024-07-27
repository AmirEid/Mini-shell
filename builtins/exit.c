/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:38 by anomourn          #+#    #+#             */
/*   Updated: 2024/07/27 17:35:15 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_exit_handler(t_list *current)
{
	t_list		*next;
	t_tkn_data	*next_string;
	int			i;
	int			list_size;

	list_size = 0;
	t_list *temp = current;
	while (temp != NULL)
	{
		list_size++;
		temp = temp->next;
	}
	if (current->next != NULL)
	{
		next = current->next;
		next_string = (t_tkn_data *)next->content;
		i = -1;
		if (list_size > 2)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			exit(1);
		}
		else if (list_size == 2)
		{
			while(next_string->token[++i])
			{
				if (!ft_isdigit(next_string->token[i]))
				{
					ft_putstr_fd("bash: exit: ", 2);
					ft_putstr_fd(next_string->token, 2);
					ft_putstr_fd(": numeric argument required\n", 2);
					exit(2);
				}
			}
		}
	}
	return;
}

void	ft_exit(t_list *args)
{
	int	exit_code = 0;

	ft_exit_handler(args);
	if (args->next != NULL)
	{
		t_tkn_data *arg_data = (t_tkn_data *)args->next->content;
		exit_code = ft_atoi(arg_data->token);
	}
	ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}
