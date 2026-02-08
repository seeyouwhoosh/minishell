/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:17:48 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 21:54:55 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	err(t_str str)
{
	ft_putstr_fd("mnsh: ", 2);
	ft_putstr_fd(str.str, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	free(str.str);
	return (1);
}

int	opening(t_why a, int mode, t_str str)
{
	int	fd;

	if (mode == HERE_DOC)
	{
		free_pointer(&(a.cmd->here_doc));
		a.cmd->here_doc = str.str;
		return (SUCCESS);
	}
	fd = ft_open(str.str, mode);
	if (fd < 0)
		return (err(str));
	if (mode == APPEND || mode == OUTFILE)
	{
		if (a.cmd->outfile != 1)
			close(a.cmd->outfile);
		a.cmd->outfile = fd;
	}
	else
	{
		if (a.cmd->infile)
			close(a.cmd->infile);
		a.cmd->infile = fd;
	}
	return (SUCCESS);
}
