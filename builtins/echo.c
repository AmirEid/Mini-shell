/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:54:51 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/31 22:23:33 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//!!!! FIX THIS !!!! check if type is meta_dol print by skipping spaces 
//export c="   4 6   "
//export
//....
//...
//declare -x c="   4 6   "$
//rpaic@c2r3p9:~$ echo $c | cat -e
//4 6$

//rpaic@c2r3p9:~$ echo "    4 6   " | cat -e
//    4 6   $

#include "../headers/minishell.h"

bool	till(int type)
{
	if ((type == META_PIPE) || (type == META_REDIR_OUT))
		return (false);
	if ((type == META_HEREDOC) || (type == META_REDIR_IN))
		return (false);
	return (true);
}

static bool	is_white(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (true);
	return (false);
}

static void	write_no_white(char *str)
{
	char	*now;
	int		flag;

	flag = 0;
	if (!str)
		return ;
	now = str;
	while (*now && is_white(*now))
		now++;
	while (*now)
	{
		if (is_white(*now))
			flag = 1;
		if (ft_isprint(*now))
		{
			if (flag)
				write(STDOUT_FILENO, " ", 1);
			flag = 0;
			write(STDOUT_FILENO, now, 1);
		}
		now++;
	}
}

void	ft_echo(t_list *cur_token)
{
	bool	nl;
	t_list	*curr;

	curr = cur_token->next;
	nl = true;
	if (curr && !ft_strncmp(((t_tkn_data *)(curr->content))->token, "-n",
		ft_strlen(((t_tkn_data *)(curr->content))->token)))
	{
		nl = false;
		curr = curr->next;
	}
	while (curr && till(((t_tkn_data *)(curr->content))->type))
	{
		if (((t_tkn_data *)(curr->content))->type == META_DOL)
			write_no_white(((t_tkn_data *)(curr->content))->token);
		else
			write(STDOUT_FILENO, ((t_tkn_data *)(curr->content))->token,
				ft_strlen(((t_tkn_data *)(curr->content))->token));
		curr = curr->next;
		if (curr && till(((t_tkn_data *)(curr->content))->type))
			write(STDOUT_FILENO, " ", 1);
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
}
