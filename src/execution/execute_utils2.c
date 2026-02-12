/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:53:55 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 20:02:09 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_exit(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

char	*get_path(char *cmd, char **env)
{
	size_t	i;
	char	**split_paths;
	char	*pathplus;
	char	*path;

	if (!env || !cmd)
		return (NULL);
	i = -1;
	while (env[++i] && !ft_strnstr(env[i], "PATH=", 5))
		;
	split_paths = ft_split(env[i] + 5, ':');
	if (!split_paths)
		return (NULL);
	i = -1;
	while (split_paths[++i])
	{
		pathplus = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(pathplus, cmd);
		free(pathplus);
		if (!access(path, X_OK))
			return (ft_freesplit(split_paths), path);
		free(path);
	}
	ft_freesplit(split_paths);
	return (NULL);
}
