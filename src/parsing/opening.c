/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 16:17:48 by gcassi-d          #+#    #+#             */
/*   Updated: 2026/02/08 21:23:43 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(str.str);
	if (fd < 0)
		return (error_msg("mnsh", str.str, "no such file or directory", 1));
	if (mode == APPEND || mode == INFILE)
		a.cmd->outfile = fd;
	else
		a.cmd->infile = fd;
	return (SUCCESS);
}
