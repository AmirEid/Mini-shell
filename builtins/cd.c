/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:33:25 by anoukmourna       #+#    #+#             */
/*   Updated: 2024/06/24 19:16:52 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

// void	ft_cd(t_list *tokens, t_list *env)
// {
// 	char	*old_pwd;
// 	char	cwd[1024];
// 	char	*path;
// 	char	*new_pwd;

// 	if (!tokens || !tokens->next)
// 	{
// 		path = search_env(env, "HOME");
// 		if (!path)
// 		{
// 			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 29);
// 			return ;
// 		}
// 	}
// 	old_pwd = getcwd(cwd, sizeof(cwd));
// 	if (old_pwd == NULL)
// 	{
// 		perror("getcwd");
// 		return ;
// 	}
// 	if (chdir(path) != 0)
// 	{
// 		perror("cd");
// 		return ;
// 	}
// 	new_pwd = getcwd(cwd, sizeof(cwd));
// 	if (new_pwd == NULL)
// 	{
// 		perror("getcwd");
// 		return ;
// 	}
// 	set_env("OLDPWD", old_pwd, env);
// 	set_env("PWD", new_pwd, env);
// }

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

/* Updates the environment variable that stores the current working directory */
static void	ft_replace_pwd(char *var, char *new, t_data *data)
{
	char	*res;
	int		len;
	int		i;
	char	*temp;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
		{
			temp = ft_strdup(var);
			res = ft_strjoin2(temp, new);
			free(temp);
			free(data->env[i]);
			data->env[i] = ft_strdup(res);
			free(res);
			break ;
		}
	}
}

/* Updates the environment variable with the previous working directory */
static void	ft_change_oldpwd(t_data *data)
{
	free(data->old_pwd);
	data->old_pwd = ft_strdup(data->pwd);
	ft_replace_pwd("OLDPWD=", data->old_pwd, data);
}

/* Changes the current working directory and update the PWD environment variable */
static int	ft_change_directory(t_list *tokens, t_data *data)
{
	if (data->env)
		ft_change_oldpwd(data);
	if (chdir((char *)tokens->next->content) != 0)
	{
		printf("minishell: cd: %s: %s\n", ((char *)tokens->next->content), strerror(errno));
		return (1);
	}
	if (data->pwd)
		free(data->pwd);
	data->pwd = malloc(sizeof(char) * 4096);
	if (!data->pwd)
		return (1);
	if (!getcwd(data->pwd, 4096) || !data->pwd)
		return (1);
	if (data->env)
		ft_replace_pwd("PWD=", data->pwd, data);
	return (0);
}

/* Checks special case like 'cd -' and calls ft_change_directory to change the directory */
int	ft_cd(t_list *tokens, t_data *data)
{
    int		arg_count;
    t_list	*current;

    arg_count = 0;
    current = tokens->next; //on commence après le cd
    while (current)
    {
        arg_count++;
        current = current->next;
    }
    if (arg_count > 0 && strcmp(((char *)tokens->next->content), "-") == 0)
    {
        if (!((char *)tokens->next->content)[1])
        {
            ft_pwd(data);
            return (0);
        }
    }
    if (arg_count > 1)
    {
        printf("minishell: cd: too many arguments\n");
        return (1);
    }
    return (ft_change_directory(tokens, data));
}