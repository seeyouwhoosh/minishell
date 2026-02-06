/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcassi-d <gcassi-d@42urduliz.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:11:29 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/06 00:40:37 by gcassi-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_exit_code(t_why a, t_str *str, size_t i)
{
	char	*c;
	int		j;

	c = ft_itoa(a.cmdtab->exit_code);
	if (!c)
		return (free(str->str), MALLOC);
	j = 0;
	while (c[j])
	{
		if (expand(str))
			return (free(c), MALLOC);
		str->str[str->len++] = c[j];
		j++;
	}
	return (free(c), SUCCESS);
}
