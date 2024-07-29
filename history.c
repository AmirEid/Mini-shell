/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:09:31 by anomourn          #+#    #+#             */
/*   Updated: 2024/07/29 18:01:58 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

// void print_history(t_data *data)
// {
//     int i;

//     i = 0;
//     while (i < data->list_size)
//     {
//         ft_printf("%d: %s\n", i, ((t_tkn_data *)ft_lstlast(data->tokens)->content)->token);
//         i++;
//         data->tokens = data->tokens->next;
//     }
// }

// void ft_clear_history(t_data *data)
// {
//     t_list *current;
//     t_list *next;

//     current = data->tokens;
//     while (current != NULL)
//     {
//         next = current->next;
//         free(((t_tkn_data *)current->content)->token);
//         free(current->content);
//         free(current);
//         current = next;
//     }
//     data->tokens = NULL;
//     data->list_size = 0;
// }

