/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:12:39 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/08 18:33:19 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

size_t most_right_eq(char *str1, char *str2)
{
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    while (str1[i] != '\0' && str1[i] != '=')
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

size_t  idx_of_eq_or_plus(char *str_plus, char *str_eq)
{
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    while (str_plus[i] != '+')
        i++;
    while (str_eq[j] && str_eq[j] != '=')
        j++;
    if (i > j)
        return (i);
    return (j);
}

char	*strjoin_free(char *s1, char *s2, int frees)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
    if (frees >= 1)
    {
        if (frees >= 2)
            free_null(s2);
        free_null(s1);
	}
    return (str);
}

void add_toenv_skip_plus(t_data data, char *str)
{
    t_list  *new_node;
    char   *new_entry;
    int     i;
    int     j;
    int     len;

    i = 0;
    j = 0;
    len = ft_strlen(str);
    new_entry = malloc(len * sizeof(char));
    // if (!new_entry)
    //     garbage_collector(data);
    while (str[i] != '+')
        new_entry[j++] = str[i++];
    i++;
    while (str[i] != '\0')
        new_entry[j++] = str[i++];
    new_entry[j] = '\0';
    new_node = ft_lstnew(new_entry);
    ft_lstadd_back(&data.mini_env, new_node);
}