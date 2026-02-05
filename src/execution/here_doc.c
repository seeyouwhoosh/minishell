/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:50:45 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:50:58 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	here_doc_put(char *limiter, size_t n_cmds)
{
	char	*input;
	char	*new_limiter;

	new_limiter = ft_strjoin(limiter, "\n");
	if (!new_limiter)
		return ;
	while (--n_cmds > 0)
		ft_putstr_fd("pipe ", 1);
	ft_putstr_fd("here_doc>", 1);
	input = get_next_line(0);
	while (input)
	{
		if (!ft_strcmp(input, new_limiter))
		{
			free(new_limiter);
			free(input);
			exit(0);
		}
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
		ft_putstr_fd("here_doc>", 1);
		input = get_next_line(0);
	}
}

int	here_doc(char *limiter, size_t n_cmds)
{
	pid_t	read;
	int		fd[2];

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	read = fork();
	if (read == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!read)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		here_doc_put(limiter, n_cmds);
		return (0);
	}
	else if (read > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(read, NULL, 0);
	}
	return (0);
}
