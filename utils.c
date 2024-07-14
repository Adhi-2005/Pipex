/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adshafee <adshafee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:39:23 by adshafee          #+#    #+#             */
/*   Updated: 2024/07/14 11:58:11 by adshafee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*get_path(char **env)
{
	int		i;
	int		j;
	char	*store;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		store = ft_substr(env[i], 0, j);
		if (ft_strcmp("PATH", store) == 0)
		{
			free(store);
			return (env[i] + j + 1);
		}
		free(store);
		i++;
	}
	return (NULL);
}

char *find_path(char *cmd, char **env)
{
	char	**path;
	char	**obtn_cmds;
	char	*cmd_path;
	int		i;

	i = 0;
	path = ft_split(get_path(env), ':');
	obtn_cmds = ft_split(cmd, ' ');
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(cmd_path, obtn_cmds[0]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			ft_free_array(obtn_cmds);
			return (cmd_path);
		}
		i++;
		free(cmd_path);
	}
	ft_free_array(obtn_cmds);
	ft_free_array(path);
	return (cmd);
}