/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:53:21 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 00:37:17 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void	ft_parsing(t_data *data);
void	define_builtins(t_list *tokens);
void	expander(t_list *tokens, t_data *data);
char	**get_cmd_path(t_list *mini_env, t_data *data);
void	define_commands(t_list *tokens, char **path);
void	ft_parser(t_list *tokens, t_data *data);
int		ft_get_process_num(t_list *tokens);
void	ft_organizer(t_list *tokens);
void	ft_organizer1(t_list **tokens);
void	meta_dol_expander_manager(int variable_len, char **tkn_str,
			t_data *data, t_types type);
void	dquote_expander(t_list *mini_env, int variable_len, char **tkn_str,
			t_data *data);

#endif