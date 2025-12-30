/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:58:22 by xwu               #+#    #+#             */
/*   Updated: 2025/10/24 00:46:25 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Command not found\n", 20);
	return (NULL);
}

void	exec(char *cmd, char **env)
{
	char	*path;
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (!path)
	{
		ft_freesplit(split_cmd);
		free(path);
		return ;
	}
	if (execve(path, split_cmd, env))
	{
		perror(path);
		ft_freesplit(split_cmd);
		free(path);
	}
}

void	here_doc_put(char *limiter, int fd)
{
	char	*input;
	char	*new_limiter;
	
	new_limiter = ft_strjoin(limiter, "\n");
	write(1, "\e[1;1mhere_doc> \e[0;0m", 22);
	input = get_next_line(0);
	while (input)
	{
		if (!ft_strncmp(input, new_limiter, ft_strlen(input)))
		{
			free(new_limiter);
			free(input);
			exit(0);
		}
		write(fd, input, ft_strlen(input));
		free(input);
		write(1, "\e[1;1mhere_doc> \e[0;0m", 22);
		input = get_next_line(0);
	}
}

void	get_line(int fd, char **line, size_t size)
{
	size_t	i;
	int		nread;
	char	c;

	i = 0;
	nread = read(fd, &c, 1);
	while (nread > 0)
	{
		if (i + 1 >= size)
		{
			*line = ft_realloc(*line, size, size * 2);
			size *= 2;
		}
		(*line)[i++] = c;
		if (c == '\n')
			break ;
		nread = read(fd, &c, 1);
	}
	if (nread == -1 || (!nread && !i))
	{
		free(*line);
		*line = NULL;
		return ;
	}
	(*line)[i] = '\0';
}

char	*get_next_line(int fd)
{
	char	*line;
	size_t	size;

	size = 32;
	if (fd < 0)
		return (NULL);
	line = malloc(size);
	if (!line)
		return (NULL);
	get_line(fd, &line, size);
	if (!line)
		return (NULL);
	return (line);
}
