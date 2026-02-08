/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:53:13 by xwu               #+#    #+#             */
/*   Updated: 2026/02/08 21:53:40 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str_cmd, t_cmdtab *cmdtab)
{
	(void)cmdtab;
	if (!strcmp(str_cmd, "cd"))
		return (CD);
	else if (!strcmp(str_cmd, "echo"))
		return (ECHO);
	else if (!strcmp(str_cmd, "env"))
		return (ENV);
	else if (!strcmp(str_cmd, "exit"))
		return (EXIT);
	else if (!strcmp(str_cmd, "export"))
		return (EXPORT);
	else if (!strcmp(str_cmd, "pwd"))
		return (PWD);
	else if (!strcmp(str_cmd, "unset"))
		return (UNSET);
	else
		return (-1);
}

int	builtin_cmd(t_cmd *cmd, t_cmdtab *cmdtab, int code)
{
	if (code == CD)
		return (cd(cmdtab, cmd->split_cmd));
	else if (code == ECHO)
		return (echo(cmdtab, cmd->split_cmd));
	else if (code == ENV)
		return (env(cmdtab, cmd->split_cmd));
	else if (code == EXIT)
		return (ft_exit(cmdtab, cmd->split_cmd));
	else if (code == EXPORT)
		return (export(cmdtab, cmd->split_cmd));
	else if (code == PWD)
		return (pwd(cmdtab, cmd->split_cmd));
	else if (code == UNSET)
		return (unset(cmdtab, cmd->split_cmd));
	return (-1);
}

int	exec_last_builtin(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int	exit;

	exit = is_builtin(cmd->split_cmd[0], cmdtab);
	if (exit == -1)
		return (exit);
	if (manage_infile(cmd, cmdtab))
	{
		ft_dup(cmdtab->stdin_fd, STDIN_FILENO);
		return (1);
	}
	if (manage_outfile(cmd, cmdtab))
	{
		ft_dup(cmdtab->stdout_fd, STDOUT_FILENO);
		return (1);
	}
	exit = builtin_cmd(cmd, cmdtab, exit);
	ft_dup(cmdtab->stdin_fd, STDIN_FILENO);
	ft_dup(cmdtab->stdout_fd, STDOUT_FILENO);
	return (exit);
}

/* int	exec_builtin(char *cmd, t_cmdtab *cmdtab)
{
	;
}
*/