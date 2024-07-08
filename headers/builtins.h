/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:27:02 by rpaic             #+#    #+#             */
/*   Updated: 2024/07/08 17:20:38 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void        print_env(t_data data);
//char	*get_env_value(char *key);
void        solo_export(t_data data);
t_list      *get_env(t_data data, char **env);
void	    set_env(char *name, char *path, t_list *mini_env);
char 	    *search_env(t_list *mini_env, char *variable);
char 	    *find_path(char *curr_content, char *variable);
// void	ft_cd(t_list *tokens, t_list *mini_env);
void        check_left_side_export(char *str, int *left_side_type);
t_list     *ft_export(t_data data, t_list *cur_token); //I will analize the next token and if OK put it in
size_t      biggest_strlen(char *str1, char *str2);
size_t      most_right_eq(char *str1, char *str2);

//export UTILS
void        add_toenv_skip_plus(t_data data, char *str);
char	    *strjoin_free(char *s1, char *s2, int frees);
size_t      idx_of_eq_or_plus(char *str_plus, char *str_eq);

//FREE and GARBAGE
void        free_mtx(char **path);
void        free_null(void *ptr);

#endif
