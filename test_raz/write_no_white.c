/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_no_white.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:04:26 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/05 20:52:53 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

// static bool	is_white(char c)
// {
// 	if ((c >= 9 && c <= 13) || c == ' ')
// 		return (true);
// 	return (false);
// }

// int	ft_isprint(int c)
// {
// 	if (c > 32 && c <= 126)
// 		return (1);
// 	return (0);
// }

// static void	write_no_white(char *str)
// {
// 	char	*now;
// 	int		flag;

// 	flag = 0;
// 	if (!str)
// 		return ;
// 	now = str;
// 	while (*now && is_white(*now))
// 		now++;
// 	while (*now)
// 	{
// 		if (is_white(*now))
// 			flag = 1;
// 		if (ft_isprint(*now))
// 		{
// 			if (flag)
// 				write(STDOUT_FILENO, " ", 1);
// 			flag = 0;
// 			write(STDOUT_FILENO, now, 1);
// 		}
// 		now++;
// 	}
// }

int main(void)
{
    write(1, "Hello", 5);
	write(1, NULL, 0);
	write(1, "2", 1);
    return (0);
}