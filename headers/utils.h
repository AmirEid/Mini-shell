/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmournard <anoukmournard@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:21:20 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/05 11:23:12 by anoukmourna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*strjoin_free(char *s1, char *s2, int frees);
void	free_all(t_data *data);
t_data	initialize_data();
int		check_if_empty(char *args);
void	prompt_loop(t_data *data);
void	reinitialize_data(t_data *data);

#endif