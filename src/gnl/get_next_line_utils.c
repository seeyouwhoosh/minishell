/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:36:05 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 21:07:28 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[j + i] = src[j];
		j++;
		if (dest[j + i - 1] == '\n')
			break ;
	}
	dest[i + j] = 0;
	if ((i != 0 || j != 0) && dest[j + i - 1] == '\n')
		return (1);
	return (0);
}

static void	ftr_memcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_empty_line(void)
{
	char	*p;

	p = malloc(1);
	p[0] = '\0';
	return (p);
}

int	ft_update(char **line, char *aux)
{
	char	*new;

	if (!*line)
		*line = ft_empty_line();
	new = malloc(sizeof(char) * (ft_strlen(*line) + ft_strlen(aux) + 1));
	if (!new)
	{
		free(*line);
		return (0);
	}
	new[0] = '\0';
	ft_strcat(new, *line);
	free(*line);
	*line = new;
	if (ft_strcat(new, aux))
	{
		ftr_memcpy(aux, aux + ft_strlen(aux));
		return (2);
	}
	return (1);
}
