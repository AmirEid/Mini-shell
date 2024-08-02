/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:25:05 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/02 13:12:54 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void   error_export_unset(char flag, char *str)
{
    if (flag == 'e')
        ft_putstr_fd("minishell: export: ", 2);
    else if (flag == 'u')
        ft_putstr_fd("minishell: unset: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": not a valid identifier\n", 2);
    exit_status = 1;
}

static int    str_type(char *str)
{
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	else if (ft_strchr(str, '+'))
	{
		if (*(ft_strchr(str, '+') + 1) == '=')
			return (2);
	}
	else if (ft_strchr(str, '='))
		return (1);
	return (-1);
}

static void	check_left_side(char *str, int *left_side_type)
{
    char *end;
    
    end = NULL;
    if (*left_side_type == 0)
    {
        error_export_unset('e', str);
        return ;
    }
    else if (*left_side_type == 1)
        end = ft_strchr(str, '='); //=
    else if (*left_side_type == 2)
        end = ft_strchr(str, '+'); //+=
    else
        end = str + ft_strlen(str);  //no = or +=
    while(++str != end)
    {
        if ((ft_isalnum(*str) == 0) && *str != '_')
        {
            error_export_unset('e', str);
            return ;
        }
    }
}

void	check_left_side_export(char *str, int *left_side_type)
{
	*left_side_type = str_type(str);
	check_left_side(str, left_side_type);
	//left_side_type == 0  ERROR
	//left_side_type = 1   export a=
	//left_side_type = 2   export a+=
	//left_side_type = -1  OK and alone -> export a
}
