/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:17 by aeid              #+#    #+#             */
/*   Updated: 2024/07/22 23:28:16 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static char *get_variable(char *string)
{
	int i;
	int j;
	char *variable;
	
	i = ft_strlen(string);
	memory_allocator((void **)&variable, i - 2);
	i = 0;
	j = -1;
	while (string[++i] != '\n')
		variable[++j] = string[i];
	variable[++j] = '\0';
	return (variable);
}

static void check_expansion(char *buffer, int fd, t_list *env)
{
	int i;
	char *path;
	char *variable;

	i = 0;
	path = NULL;
	variable = NULL;
	if (buffer[i] == '$')
	{
		variable = get_variable(buffer);
		path = search_env(env, variable);
		if (path)
		{
			write(fd, path, ft_strlen(path));
		}
		write(fd, "\n", 1);
		free(variable);
	}
	else
		write(fd, buffer, ft_strlen(buffer));
}


void ft_heredoc(t_list *file, t_list *env)
{
	t_tkn_data *tokendata;
	int p_errno;
	char *buffer;
	int fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		buffer = get_next_line(0);
		//handle this properly
		if (ft_strncmp(tokendata->token, buffer, ft_strlen(tokendata->token)) == 0 || buffer == NULL)
			break ;
		if (tokendata->type == SPECIAL_DQUOTE || tokendata->type == SPECIAL_SQUOTE || tokendata->type == WORD_WITH_DQUOTE_INSIDE || tokendata->type == WORD_WITH_SQUOTE_INSIDE)
			write(fd, buffer, ft_strlen(buffer));
		else
			check_expansion(buffer, fd, env);
		free(buffer);
	}
	get_next_line(-1);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		p_errno = errno;
		unlink(".heredoc");
		ft_dup2_error_manager(fd, p_errno);
	}
	dup2(fd, 0);
	close(fd);
	unlink(".heredoc");
}
