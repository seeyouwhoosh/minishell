/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:00:32 by xwu               #+#    #+#             */
/*   Updated: 2026/01/31 13:31:28 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	cmd->split_cmd = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->errfile = NULL;
	cmd->here_doc = NULL;
}
