/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:35:22 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/08 18:41:37 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_exit_list_size(t_list *current, int *again)
{
	int		list_size;
	t_list	*temp;

	list_size = 0;
	temp = current;
	while (temp && till(((t_tkn_data *)(temp->content))->type))
	{
		if (((t_tkn_data *)(temp->content))->token)
			list_size++;
		temp = temp->next;
	}
	if (list_size > 1)
	{
		if (*again == 0)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit_status = 1;
			(*again)++;
		}
	}
	return (list_size);
}

t_list	*control_first_arg(t_list *args, int *begin, t_data *data)
{
	t_list	*current;

	current = args;
	while (current && !(((t_tkn_data *)(current->content))->token))
		current = current->next;
	if (!current || !till(((t_tkn_data *)(current->content))->type))
	{
		ft_putstr_fd("exit\n", 1);
		exit_status = 0;
		free_all(data);
		free_env_list(&data->mini_env);
		exit(exit_status);
	}
	else
		check_exit_argument(((t_tkn_data *)(current->content))->token, begin, data);
	return (current);
}
//+9223372036854775807
void	ft_exit(t_list *args, t_data *data)
{
	long long int	exit_atoll;
	int				begin;
	int				printed;

	printed = 0;
	args = control_first_arg(args->next, &begin, data);
	if (count_exit_list_size(args, &printed) == 1)
	{
		check_exit_argument(((t_tkn_data *)(args->content))->token, &begin, data);
		exit_atoll = ft_atoll(((t_tkn_data *)(args->content))->token, begin, data);
	}
	else if (count_exit_list_size(args, &printed) == 0)
	{
		exit_status = 0;
		free_all(data);
		free_env_list(&data->mini_env);
		exit(exit_status);
	}
	else
		return ;
	exit_status = exit_atoll % 256;
	ft_putstr_fd("exit\n", 1);
	free_all(data);
	free_env_list(&data->mini_env);
	exit(exit_status);
}
