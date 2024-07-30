/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/30 22:06:35 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "./headers/minishell.h"

int	exit_status;

int	main (int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data = initialize_data();
	data.mini_env = get_env(data, env);
	ft_signals();
	while (1)
	{
		prompt_loop(&data);
		ft_lexer(&data);
		//printTokens(data.tokens);
		ft_parsing(&data, data.tokens);
		//printTokens(data.tokens);
		ft_execution(data.tokens, data.mini_env, &data);
		rl_on_new_line();
		add_history(data.args);
		free_all(&data);
		reinitialize_data(&data);
	}
	return 0;
}
