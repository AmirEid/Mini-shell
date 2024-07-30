/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:53:21 by aeid              #+#    #+#             */
/*   Updated: 2024/07/30 14:55:12 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

void    ft_parsing(t_data *data, t_list *tokens);
void    define_builtins(t_list *tokens);
void    expander(t_list *tokens, t_data *data);
char    **get_cmd_path(t_list *mini_env, t_data *data);
void    define_commands(t_list *tokens, char **path);
void    ft_parser(t_list *tokens, t_data *data);
char	*getTypeName(t_types type);

#endif