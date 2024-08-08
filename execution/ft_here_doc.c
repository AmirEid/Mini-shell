/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:39:17 by aeid              #+#    #+#             */
/*   Updated: 2024/08/08 22:09:06 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

// static char *get_variable(char *string, t_data *data)
// {
// 	int i;
// 	int j;
// 	char *variable;
	
// 	i = ft_strlen(string);
// 	memory_allocator((void **)&variable, i - 2, data);
// 	i = 0;
// 	j = -1;
// 	while (string[++i] != '\n')
// 		variable[++j] = string[i];
// 	variable[++j] = '\0';
// 	return (variable);
// }

static char	*get_env_vars(char *env_line)
{
	int	i;

	i = -1;
	while (env_line[++i] != '=' && env_line[i])
		;
	if (!env_line[i] || !env_line)
		return (NULL);
	return (ft_substr(env_line, 0, i));
}

static void	check_expansion(char *buffer, int fd, t_list *env, t_data *data)
{
	int		i;
	char	*var_env;
	char	*expand_value;
	t_list	*tmp;

	i = -1;
	var_env = NULL;
	tmp = env;
	expand_value = NULL;
	while (buffer[++i])
	{
		if (buffer[i] == '$')
		{
			while (tmp)
			{
				var_env = get_env_vars((char *)tmp->content);
				if (ft_strncmp(var_env, ft_strchar(buffer + i, var_env[0]), ft_strlen(var_env)) == 0)
					break ;
				free(var_env);
				var_env = NULL;
				tmp = tmp->next;
			}
			if (var_env)
			{
				expand_value = search_env(env, var_env, data);
				i += ft_strlen(var_env);
				write(fd, expand_value, ft_strlen(expand_value));
				free(var_env);
				free(expand_value);
			}
			else
				write(fd, "\n", 1);
		}
		else
			write(fd, &buffer[i], 1);
	}
}

//INSERT SIGNALS IN HERE DOC
void	ft_heredoc(t_list *file, t_list *env, t_data *data, int *redi_num)
{
	t_tkn_data	*tokendata;
	int			p_errno;
	int			fd;
	int			tp_fd;

	tp_fd = dup(0);
	tokendata = (t_tkn_data *)file->content;
	fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, ft_heredoc_handler);
	exit_status = 0;
	while (1)
	{
		dup2(data->tmp_fd, 0);
		write(0, "> ", 2);
		data->buffer_heredoc = get_next_line(0);
		if (exit_status == 130)
		{
			unlink(".heredoc");
			close(tp_fd);
			close(fd);
			free(data->buffer_heredoc);
			if (data->process_num > 1)
			{
				free_all(data);
				free_env_list(&env);
				exit(exit_status);
			}
			return ;
		}
		if (!data->buffer_heredoc)
		{
			write(2, "minishell: warning: here-document at line 5 delimited by end-of-file\n", 70);
			break ;
		}
		if (ft_strncmp(tokendata->token, data->buffer_heredoc, ft_strlen(tokendata->token)) == 0)
				break ;
		if (tokendata->type == SPECIAL_DQUOTE || tokendata->type == SPECIAL_SQUOTE || tokendata->type == WORD_WITH_DQUOTE_INSIDE || tokendata->type == WORD_WITH_SQUOTE_INSIDE)
			write(fd, data->buffer_heredoc, ft_strlen(data->buffer_heredoc));
		else
			check_expansion(data->buffer_heredoc, fd, env, data);
		free(data->buffer_heredoc);
	}
	dup2(tp_fd, 0);
	close(fd);
	if (data->buffer_heredoc)
		 free(data->buffer_heredoc);
	if ((*redi_num) - 1 == 0)
	{
		fd = open(".heredoc", O_RDONLY);
		if (fd == -1)
		{
			p_errno = errno;
			unlink(".heredoc");
			ft_dup2_error_manager(fd, p_errno);
		}
		dup2(fd, 0);
		close(fd);
	}
	(*redi_num)--;
	unlink(".heredoc");
	close(tp_fd);
}
