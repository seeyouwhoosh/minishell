/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/02/05 01:57:00 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(char **split_cmd, t_cmdtab *cmdtab)
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
	{
		free(path);
		return (error_msg(split_cmd[0], NULL, NULL, exit));
	}
	return (0);
}

int	exec_last_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	pid_t	command;

	if (cmd->here_doc)
		here_doc(cmd->here_doc, cmdtab->n_cmds);
	else if (cmd->infile.name && open_and_dup(&(cmd->infile), STDIN_FILENO))
		return (1);
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
	{
		if (cmd->outfile.name && open_and_dup(&(cmd->outfile), STDOUT_FILENO))
			return (1);
		else
			dup2(cmdtab->stdout_fd, STDOUT_FILENO);
		exit = exec_builtin(cmd, cmdtab);
		if (exit < 0)
			exit = exec(cmd->split_cmd, cmdtab);
		return (exit);
	}
	waitpid(command, &exit, 0);
	return (exit);
}

int	child_process(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2])
{
	int	exit;

	if (cmd->outfile.name && open_and_dup(&(cmd->outfile), STDOUT_FILENO))
		return (1);
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
	}
	exit = exec_builtin(cmd, cmdtab);
	if (exit < 0)
		exit = exec(cmd->split_cmd, cmdtab);
	return (exit);
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		exit;
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	if (cmd->here_doc && here_doc(cmd->here_doc, cmdtab->n_cmds))
		return (1);
	else if (cmd->infile.name && open_and_dup(&(cmd->infile), STDIN_FILENO))
		return (1);
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
		exit = child_process(cmd, cmdtab, fd);
	else if (command > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(command, &exit, 0);
	}
	return (exit);
}
