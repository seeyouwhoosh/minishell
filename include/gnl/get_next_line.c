/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:35:28 by gcassi-d          #+#    #+#             */
/*   Updated: 2025/12/12 00:03:26 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static int	ft_read(int fd, char *buff, char **line)
{
	ssize_t	i;

	i = read(fd, buff, BUFFER_SIZE);
	if (i == -1)
	{
		if (*line)
			free(*line);
		*line = NULL;
		return (-1);
	}
	buff[i] = 0;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	aux[BUFFER_SIZE + 1];
	ssize_t		check;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (aux[0] == 0)
		{
			check = ft_read(fd, aux, &line);
			if (check == 0 || !(*aux) || check == -1)
				return (line);
		}
		check = ft_update(&line, aux);
		if (!check)
			return (NULL);
		else if (check == 2)
			return (line);
		check = ft_read(fd, aux, &line);
		if (check == -1)
			return (NULL);
	}
}

#include <stdio.h>

int main()
{
	int fd = open("prueba.txt", O_RDONLY);
	char* line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
 