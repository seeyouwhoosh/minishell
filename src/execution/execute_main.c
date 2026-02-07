/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:51:44 by xwu               #+#    #+#             */
/*   Updated: 2026/02/07 14:24:10 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_all(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	while (cmdtab->n_cmds - 1 > ++i)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i, cmdtab);
	cmdtab->exit_code = exec_last_cmd(cmdtab->cmds + i, cmdtab);
	free_cmds(cmdtab);
	return (cmdtab->exit_code);
}
