/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:12:39 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/07 22:04:14 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

size_t most_right_eq(char *str1, char *str2)
{
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    while (str1[i] != '\0' && str2[i] != '=')
        i++;
    while (str2[j] != '\0' && str2[j] != '=')
        j++;
    if (i > j)
        return (i);
    return (j);
}

size_t   biggest_strlen(char *str1, char *str2)
{
    if (ft_strlen(str1) > ft_strlen(str2))
        return (ft_strlen(str1));
    return (ft_strlen(str2));
}