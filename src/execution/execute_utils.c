/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xwu <xwu@student.42urduliz.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 10:45:02 by xwu               #+#    #+#             */
/*   Updated: 2026/02/08 19:27:02 by xwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_bin(char **split_cmd, t_cmdtab *cmdtab)
{
	char	*path;
	int		ext;

	path = get_path(split_cmd[0], cmdtab->env);
	if (!path)
	{
		ext = error_msg("mnsh", split_cmd[0], "command not found", 127);
		ft_freesplit(split_cmd);
		free(path);
		return (ext);
	}
	ext = execve(path, split_cmd, cmdtab->env);
	if (ext)
		return (free(path), error_msg(split_cmd[0], NULL, NULL, ext));
	return (0);
}

int	exec_last_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		ext;
	pid_t	command;

	if (manage_infile(cmd, cmdtab))
		exit(EXIT_FAILURE);
	ext = exec_builtin(cmd, cmdtab);
	if (ext != -1)
		return (ext);
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	ext = 0;
	if (!command)
	{
		if (just_redirection(cmd))
			exit(EXIT_SUCCESS);
		if (manage_outfile(cmd, cmdtab))
			exit(EXIT_FAILURE);
		ext = exec_bin(cmd->split_cmd, cmdtab);
		exit(ext);
	}
	waitpid(command, &ext, 0);
	return (ext);
}

int	exec_pipe_cmd(t_cmd *cmd, t_cmdtab *cmdtab, int fd[2])
{
	int	ext;

	if (cmd->outfile != 1 && ft_dup(cmd->outfile, STDOUT_FILENO))
		return (1);
	else
	{
		close(fd[0]);
		if (ft_dup(fd[1], STDOUT_FILENO))
			return (1);
	}
	ext = exec_bin(cmd->split_cmd, cmdtab);
	return (ext);
}

void	exec_p_subprocess(t_cmdtab *cmdtab, t_cmd *cmd, int fd[2])
{
	if (manage_infile(cmd, cmdtab))
		exit(EXIT_FAILURE);
	if (!cmd->split_cmd)
	{
		ft_putendl_fd(0, 1);
		exit(EXIT_SUCCESS);
	}
	if (exec_pipe_cmd(cmd, cmdtab, fd))
		exit(EXIT_FAILURE);
}

int	exec_cmd(t_cmd *cmd, t_cmdtab *cmdtab)
{
	int		ext;
	int		fd[2];
	pid_t	command;

	if (pipe(fd))
		return (error_msg("pipe", NULL, NULL, EPIPE));
	ext = exec_builtin(cmd, cmdtab);
	if (ext != -1)
		return (ext);
	ext = 0;
	command = fork();
	if (command == -1)
		return (error_msg("fork", NULL, NULL, ENOMEM));
	if (!command)
		exec_p_subprocess(cmdtab, cmd, fd);
	close(fd[1]);
	if (ft_dup(fd[0], STDIN_FILENO))
		return (1);
	waitpid(command, &ext, 0);
	return (ext);
	free_cmdtab(cmdtab);
}
