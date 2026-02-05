/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:11:29 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/05 23:02:57 by xwu              ###   ########.fr       */
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
