/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:50:45 by xwu               #+#    #+#             */
/*   Updated: 2026/02/08 19:46:14 by xwu              ###   ########.fr       */
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

void	eof_warning_message(size_t nline, char *limiter)
{
	ft_putstr_fd("warning: here-document at line ", 1);
	ft_putstr_fd(ft_atoi(nline), 1);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 1);
	ft_pustr_fd(limiter, 1);
	ft_pustr_fd("')", 1);
}

void	put_heredoc_prompt(size_t n_cmds)
{
	while (--n_cmds > 0)
		ft_putstr_fd("pipe ", 1);
	ft_putstr_fd("here_doc> ", 1);
}

void	here_doc_put(char *limiter, size_t n_cmds)
{
	char	*input;
	char	*new_limiter;
	int		nline;

	new_limiter = ft_strjoin(limiter, "\n");
	if (!new_limiter)
	return ;
	put_heredoc_prompt(n_cmds);
	input = get_next_line(0);
	nline = 0;
	while (input)
	{
		if (!ft_strcmp(input, new_limiter))
		{
			free(new_limiter);
			free(input);
			exit(0);
		}
		ft_putstr_fd(input, 1);
		free(input);
		put_heredoc_prompt(n_cmds);
		input = get_next_line(0);
		nline++;
	}
	return (eof_warning_message(nline, limiter), 0);
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
		here_doc_put(limiter, n_cmds);
		if (ft_dup(fd[1], STDOUT_FILENO))
			exit(1);
		exit(0);
	}
	else if (read > 0)
	{
		close(fd[1]);
		if (ft_dup(fd[0], STDIN_FILENO))
			return (1);
		waitpid(read, NULL, 0);
	}
	return (0);
}
