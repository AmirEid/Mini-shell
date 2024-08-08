/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/09 00:21:18 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_types
{
	SPECIAL_SQUOTE,
	SPECIAL_DQUOTE,
	META_DOL,
	META_PIPE,
	META_REDIR_IN,
	META_REDIR_OUT,
	META_APPEND,
	META_HEREDOC,
	META_STATUS,
	WORD_EXPORT,
	WORD_UNSET,
	WORD_ENV,
	WORD_ECHO,
	WORD_CD,
	WORD_EXIT,
	WORD_PWD,
	WORD_DOL,
	WORD,
	WORD_WITH_DQUOTE_INSIDE,
	WORD_WITH_SQUOTE_INSIDE,
	COMMAND,
}			t_types;

typedef struct s_tkn_data
{
	char	*token;
	t_types	type;
	int		variable_len;
	char	*cmd_exec_path;
}			t_tkn_data;

void		ft_lexer(t_data *data);
void		memory_allocator(void **ptr, size_t size, t_data *data);
void		ft_meta_token(t_data *data, t_types type);
int			ft_isquote(int c);
int			ft_ismeta(int c);
int			ft_special_token(t_data *data, t_types type);
int			ft_word_token(t_data *data, t_types type);
void		dollar_meta(t_data *data, t_list *node, t_tkn_data *token);
void		pipe_meta(t_data *data, t_list *node, t_tkn_data *token);
void		redirect_meta(t_data *data, t_list *node, t_tkn_data *token);
void		get_variable_len(t_data *data, int dol_position, int *variable_len);
void		assign_nodes(t_list *node, t_tkn_data *token, t_data *data);
char		*special_token_handler(t_data *data, t_tkn_data *token,
				int *quote_flag, int prev);
int			dollar_counter_lexer(char *args, int current);
void		copy_assign(char *string, t_data *data, t_tkn_data *token,
				t_list *node);
void		quote_removal_copy(char *string, t_data *data, t_tkn_data *token,
				t_list *node, int quote_flag);
void		ft_copier(int *i, int c, char *string, t_data *data,
				int *quote_flag);
void		ft_assign_word_token(int *q_flag, t_tkn_data **token, char **string,
				t_types type);
void		ft_copier_dol(int *i, int c, char *string, t_data *data,
				int *quote_flag);
void		handle_meta_status(t_data *data, t_tkn_data *token);

#endif