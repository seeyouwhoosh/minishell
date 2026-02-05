/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:51:44 by xwu               #+#    #+#             */
/*   Updated: 2026/02/06 00:04:50 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_all(t_cmdtab *cmdtab)
{
	size_t	i;

	i = 0;
	while (cmdtab->n_cmds > ++i)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i - 1, cmdtab);
	cmdtab->exit_code = exec_last_cmd(cmdtab->cmds + i, cmdtab);
	free_cmds(cmdtab);
	return (cmdtab->exit_code);
}
