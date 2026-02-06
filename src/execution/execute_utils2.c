/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/02/06 20:19:56 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_bin(char **split_cmd, t_cmdtab *cmdtab)
{
	char	*path;
	int		exit;

	path = get_path(split_cmd[0], cmdtab->env);
	if (!path)
	{
		ft_freesplit(split_cmd);
		free(path);
		return (error_msg("minishell", split_cmd[0], "Command not found", 127));
	}
	exit = execve(path, split_cmd, cmdtab->env);
	if (exit)
		return (free(path), error_msg(split_cmd[0], NULL, NULL, exit));
	return (0);
}

int	exec_last_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	pid_t	command;

	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		if (manage_infile(cmd, cmdtab))
			return (1);
		if (!cmd->split_cmd)
			return (ft_putendl_fd(0, 1), 0);
		if (cmd->outfile && ft_dup(cmd->outfile, STDOUT_FILENO))
			return (1);
		else if (ft_dup(cmdtab->stdout_fd, STDOUT_FILENO))
			return (1);
		exit = exec_builtin(cmd, cmdtab);
		if (exit == -1)
			exit = exec_bin(cmd->split_cmd, cmdtab);
		return (exit);
	}
	waitpid(command, &exit, 0);
	return (exit);
}

int	child_process(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2])
{
	int	exit;

	if (cmd->outfile && ft_dup(cmd->outfile, STDOUT_FILENO))
		return (1);
	else
	{
		close(fd[0]);
		if (ft_dup(fd[1], STDOUT_FILENO))
			return (1);
	}
	exit = exec_builtin(cmd, cmdtab);
	if (exit == -1)
		exit = exec_bin(cmd->split_cmd, cmdtab);
	return (exit);
}

int	manage_infile(t_cmd *cmd, t_cmdtab *cmdtab)
{
	if (cmd->here_doc && here_doc(cmd->here_doc, cmdtab->n_cmds))
		return (1);
	if (cmd->infile && cmd->last != INFILE && ft_dup(cmd->infile, STDIN_FILENO))
		return (1);
	return (0);
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		if (manage_infile(cmd, cmdtab))
			return (1);
		if (!cmd->split_cmd)
			return (ft_putendl_fd(0, 1), 0);
		if (child_process(cmd, cmdtab, fd))
			return (1);
		return (0);
	}
	close(fd[1]);
	if (ft_dup(fd[0], STDIN_FILENO))
		return (1);
	waitpid(command, &exit, 0);
	return (exit);
}
