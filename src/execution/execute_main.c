/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:51:44 by xwu               #+#    #+#             */
/*   Updated: 2026/02/12 20:11:28 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_all(t_cmdtab *cmdtab)
{
	size_t	i;

	i = -1;
	if (manage_heredoc(cmdtab))
		return (free_cmds(cmdtab), 1);
	while (cmdtab->n_cmds > ++i + 1)
		cmdtab->exit_code = exec_cmd(cmdtab->cmds + i, cmdtab);
	cmdtab->exit_code = exec_last_cmd(cmdtab->cmds + i, cmdtab);
	free_cmds(cmdtab);
	ft_dup(cmdtab->stdin_fd, STDIN_FILENO);
	ft_dup(cmdtab->stdout_fd, STDOUT_FILENO);
	return (cmdtab->exit_code);
}
