/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:58:22 by xwu               #+#    #+#             */
/*   Updated: 2026/01/15 16:57:28 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

int	ft_open(const char *filename, char mode)
{
	int	fd;

	fd = -1;
	if (mode == 'r')
		fd = open(filename, O_RDONLY);
	else if (mode == 'w')
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 'a')
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror(filename);
		exit (EXIT_FAILURE);
	}
	return (fd);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	char	*dest;
	char	*cptr;
	size_t	i;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	cptr = (char *)ptr;
	dest = malloc(size);
	if (!dest)
		return (NULL);
	if (!ptr)
		return (dest);
	i = -1;
	while (++i < old_size && i < size)
		dest[i] = cptr[i];
	free(ptr);
	return (dest);
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

void	here_doc_put(char *limiter, int fd)
{
	char	*input;
	char	*new_limiter;

	new_limiter = ft_strjoin(limiter, "\n");
	write(1, "\e[1;1mhere_doc> \e[0;0m", 22);
	input = get_next_line(0);
	while (input)
	{
		if (!ft_strcmp(input, new_limiter))
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

void	here_doc(char *limiter)
{
	pid_t	read;
	int		fd[2];

	if (pipe(fd))
		return (perror("Pipe failed"));
	read = fork();
	if (!read)
	{
		close(fd[0]);
		here_doc_put(limiter, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (read > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(read, NULL, 0);
	}
}
