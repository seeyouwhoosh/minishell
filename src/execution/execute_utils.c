/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:53:55 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:54:39 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, char **env)
{
	size_t	i;
	char	**split_paths;
	char	*pathplus;
	char	*path;

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

int	ft_open(const char *filename, int mode)
{
	int	fd;

	fd = -1;
	if (mode == INFILE)
		fd = open(filename, O_RDONLY);
	else if (mode == OUTFILE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

int	open_and_dup(t_file *file, int og_fd)
{
	file->fd = ft_open(file->name, file->mode);
	if (file->fd == -1)
		return (error_msg(file->name, NULL, NULL, 1));
	if (dup2(file->fd, og_fd) == -1)
		return (error_msg("dup2", NULL, NULL, 1));
	close(file->fd);
	return (0);
}