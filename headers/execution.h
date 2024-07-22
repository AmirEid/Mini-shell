/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:27:22 by aeid              #+#    #+#             */
/*   Updated: 2024/07/22 21:42:31 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# define MAX_PROCESS_NUM 100

void ft_execution(t_list *tokens, t_list *env, t_data *data);
void ft_execute_routine(t_list *tokens, t_list *env, t_data *data);
void open_files_errors_manager(int fd, char *file_name, int errnum);
void ft_dup2_error_manager(int fd, int errnum);
void ft_heredoc(t_list *file, t_list *env);
void ft_redir_in(t_list *file);
void ft_redir_append(t_list *file);
void ft_command_execution(t_list *tokens, t_list *env, t_list *current);
void ft_redir_out(t_list *file);
void create_pipes_and_execution(t_list *args[], int process_num, t_list *env, t_data *data);
void close_pipes(int pipe_fd[], int process_num);


#endif