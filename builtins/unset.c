/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:57:21 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/22 13:25:37 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void  ft_unset(t_data data, t_list *cur_token)
{
    char    *str;
    t_list  *actual_node;
    t_list  *temp;

    actual_node = cur_token->next;
    while (actual_node)
    {
        actual_node = actual_node->next;
    }
}

