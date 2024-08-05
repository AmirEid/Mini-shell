/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:09:50 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/05 20:47:08 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	skip_null_tokens(t_list **cur_token)
{
	*cur_token = (*cur_token)->next;
	while (*cur_token && !((t_tkn_data *)((*cur_token)->content))->token)
		*cur_token = (*cur_token)->next;
}

void	check_nl(bool nl)
{
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
}
