/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:53:21 by aeid              #+#    #+#             */
/*   Updated: 2024/08/05 11:22:48 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include	"minishell.h"

void	ft_parsing(t_data *data, t_list *tokens);
void	define_builtins(t_list *tokens);
void	expander(t_list *tokens, t_data *data);
char	**get_cmd_path(t_list *mini_env, t_data *data);
void	define_commands(t_list *tokens, char **path);
void	ft_parser(t_list *tokens, t_data *data);
int		ft_get_process_num(t_list *tokens);

#endif