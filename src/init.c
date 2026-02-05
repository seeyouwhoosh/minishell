/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:24:51 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	(void)cmdtab;
	cmd->split_cmd = NULL;
	cmd->here_doc = NULL;
	cmd->infile.name = NULL;
	cmd->infile.fd = STDIN_FILENO;
	cmd->infile.mode = OUTFILE;
	cmd->outfile.name = NULL;
	cmd->outfile.fd = STDOUT_FILENO;
	return (0);
}
